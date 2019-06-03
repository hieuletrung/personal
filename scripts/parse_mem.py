#!/usr/bin/python

import csv
import numpy as np
import pandas as pd
import os
import re
import sys

def read_mem_file(file_name, ignore_classes=[], ignore_packages=()):
    reader = csv.reader(open(file_name, "rb"), delimiter=',', quoting=csv.QUOTE_NONE)

    header = []
    records = []
    fields = 3

    if ignore_classes == None:
        ignore_classes = [] 
    if ignore_packages == None:
        ignore_packages = ()

    for row, record in enumerate(reader):
        if len(record) != fields:
            # if reaching line with NATIVE MEMORY USAGE end the parsing
            if record[0].strip() == "NATIVE MEMORY USAGE":
                break
        else:
            # if reaching line with Class, Memory Used (bytes), Object Count, use it as header
            if record[0] == "Class":
                record[1] = "Memory Used"
                header = map(str.strip, record)
            elif record[0] in ignore_classes:
                continue
            elif record[0].startswith('[L'):
                # Skip array
                continue
            elif record[0].startswith(ignore_packages):
                # Skip some package
                continue
            else:
                records.append(record)

    # ['Class', 'Memory Used', 'Object Count']
    df=pd.DataFrame.from_records(data=records, columns=header)
    df = df.drop_duplicates()
    return df, header

def do_my_diff(df_orig):
    header = df_orig[0].columns
    count_hdr = header[1]
    df_final = df_orig[0]
    # Save the start count
    df_final[str.format('{0} (start)', count_hdr)] = df_final[count_hdr]
    diff_column = []

    # Loop through the dump list object count and check the diff
    # Store it in diff_(index) column
    for i in range(1, len(df_orig)):
        col_name = str.format('diff_{0}',(i))
        diff_column.append(col_name)

        df_final = df_final.merge(df_orig[i], on=header[0])
        diff = df_final[str.format('{0}_y', count_hdr)] - df_final[str.format('{0}_x', count_hdr)]
        df_final[col_name] = diff

        # Drop the auto generated _x, _y column and save the current column for next iteration
        df_final = df_final.drop(columns=[str.format('{0}_x', count_hdr)])
        df_final = df_final.rename(columns={str.format('{0}_y', count_hdr): count_hdr})
    
    # store the end column
    df_final[str.format('{0} (end)', count_hdr)] = df_final[count_hdr]
    df_final = df_final.drop(columns=[count_hdr])

    df_final.sort_values(by=diff_column, inplace=True, ascending=False)
    df_final.set_index(header[0], inplace=True)

    return df_final

ignore_class = [
    '[S', '[J', '[C', '[I', '[B', '<native>', '[Z',
    'java/lang/Class', '[Ljava/lang/Class;', 
    'java/lang/String', '[Ljava/lang/String;',
    'java/lang/Integer', '[Ljava/lang/Integer;',
    'java/lang/Long', '[Ljava/lang/Long;',
    'java/lang/Object', '[Ljava/lang/Object;',
    'java/util/Vector', '[Ljava/util/Vector;',
    'java/util/ArrayList', '[Ljava/util/ArrayList;',
    'java/util/LinkedList', '[Ljava/util/LinkedList;', 'java/util/LinkedList$Link',
    'java/util/HashMap', '[Ljava/util/HashMap;', 
    'java/util/HashMap$Entry', '[Ljava/util/HashMap$Entry;',
    'java/util/Hashtable$Entry', '[Ljava/util/Hashtable$Entry;',
    'java/util/Hashtable', 'L[java/util/Hashtable;',
    'java/util/Date',
    'java/lang/StringBuffer',
]

ignore_package = (
    'java/',
)

# Get list of memory file sort by create time
file_pattern = r'siegemem.prof-*'
search_dir = sys.argv[1]

files = [f for f in os.listdir(search_dir) if re.match(file_pattern, f)] # filter(os.path.isfile, os.listdir(search_dir))
files = [os.path.join(search_dir, f) for f in files] # add path to each file
files.sort(key=lambda x: os.path.getmtime(x))

df = []
df_obj_sz = []
df_obj_cnt = []
diff_column = []

# Read the memory files into DataFrames
for f in files:
    df_tmp, header = read_mem_file(f, ignore_class, ignore_package)
    df_tmp[header[1]] = df_tmp[header[1]].astype(int)
    df_tmp[header[2]] = df_tmp[header[2]].astype(int)
    df_tmp_obj_sz = df_tmp[[header[0], header[1]]]
    df_tmp_obj_cnt = df_tmp[[header[0], header[2]]]
    df.append(df_tmp)
    df_obj_sz.append(df_tmp_obj_sz)
    df_obj_cnt.append(df_tmp_obj_cnt)

df_obj_cnt_final = do_my_diff(df_obj_cnt)

# df_obj_cnt_final = df_obj_cnt[0]
# # Save the start object count
# df_obj_cnt_final['Object Count (start)'] = df_obj_cnt_final['Object Count']

# # Loop through the dump list object count and check the diff
# for i in range(1, len(df_obj_cnt)):
#     col_name = str.format('diff_{0}',(i))
#     diff_column.append(col_name)

#     df_obj_cnt_final = df_obj_cnt_final.merge(df_obj_cnt[i], on='Class')
#     diff = df_obj_cnt_final['Object Count_y'] - df_obj_cnt_final['Object Count_x']
#     df_obj_cnt_final[col_name] = diff

#     df_obj_cnt_final = df_obj_cnt_final.drop(columns=['Object Count_x'])
#     df_obj_cnt_final = df_obj_cnt_final.rename(columns={'Object Count_y': 'Object Count'})
    
# df_obj_cnt_final['Object Count (end)'] = df_obj_cnt_final['Object Count']
# df_obj_cnt_final = df_obj_cnt_final.drop(columns=['Object Count'])
# df_obj_cnt_final.sort_values(by=diff_column, inplace=True, ascending=False)
# df_obj_cnt_final.set_index('Class', inplace=True)

# --

df_obj_sz_final = df_obj_sz[0]
# Save the start object size
df_obj_sz_final = do_my_diff(df_obj_sz)

df_obj_sz_final.to_excel("output.xlsx")

# Top 10 class that has object count increase most of the time
df_tmp = df_obj_cnt_final
for i in range(1, len(df_obj_cnt)):
    if "inc_count" in df_tmp.columns:
        tmp_cnt = df_tmp["inc_count"]
    else:
        tmp_cnt = []
    index = 0
    col_name = str.format("diff_{0}", i)
    for row in df_tmp[col_name]:
        if index == len(tmp_cnt):
            tmp_cnt.append(0)

        value = tmp_cnt[index]
        if row > 0:
            value = value + 1

        tmp_cnt[index] = value
        index = index + 1

    df_tmp["inc_count"] = tmp_cnt
print "# Top 10 class that has object count increase most of the time"
print df_tmp.sort_values(by="inc_count", ascending=False)[df_tmp.inc_count > 0]

# Top 10 class that has memory increase most of the time
print "# Top 10 class that has big object count diff between start and end"
df_tmp = df_obj_cnt_final
df_tmp["diff_start_end"] = df_tmp["Object Count (end)"] - df_tmp["Object Count (start)"]
print df_tmp.sort_values(by="diff_start_end", ascending=False).head(10)
print "    "
print "# Top 10 class that has big memory diff between start and end"
df_tmp = df_obj_sz_final
df_tmp["diff_start_end"] = df_tmp["Memory Used (end)"] - df_tmp["Memory Used (start)"]
print df_tmp.sort_values(by="diff_start_end", ascending=False).head(10)

# Find inconsistent in classes