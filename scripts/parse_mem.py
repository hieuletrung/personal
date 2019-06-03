#!/usr/bin/python

import csv
import numpy as np
import pandas as pd
import os
import re
import sys

def read_mem_file(file_name, ignore_classes=[]):
    reader = csv.reader(open(file_name, "rb"), delimiter=',', quoting=csv.QUOTE_NONE)

    header = []
    records = []
    fields = 3

    if ignore_classes == None:
        ignore_classes = [] 

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
    '[S', '[J', '[C', '[I', '[B', '<native>',
    'java/lang/Class', '[Ljava/lang/Class;', 
    'java/lang/String', '[Ljava/lang/String;',
    'java/lang/Integer', '[Ljava/lang/Integer;',
]

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
    df_tmp, header = read_mem_file(f, ignore_class)
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

# Top 10 class that has memory increase most of the time
# Top 10 class that has object count increase most of the time
# Top 10 class that has big memory diff between start and end
# Top 10 class that has big object count diff between start and end


