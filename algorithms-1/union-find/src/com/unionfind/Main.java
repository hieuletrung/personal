package com.unionfind;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class Main {
    enum UFType {
        QUICK_FIND_UF,
        QUICK_UNION_UF,
        QUICK_UNION_PATH_COMPRESSION_UF,
        WEIGHT_QUICK_UNION_UF,
        WEIGHT_QUICK_UNION_PATH_COMPRESSION_UF,
    };

    public UF getUF(UFType type, int N) {
        switch (type) {
            case QUICK_FIND_UF:
                return new QuickFindUF(N);
            case QUICK_UNION_UF:
                return new QuickUnionUF(N);
            case QUICK_UNION_PATH_COMPRESSION_UF:
                return new QuickUnionPCUF(N);
            case WEIGHT_QUICK_UNION_PATH_COMPRESSION_UF:
                return new WeightQuickUnionPCUF(N);
            case WEIGHT_QUICK_UNION_UF:
                return new WeightQuickUnionUF(N);
            default:
                return null;
        }
    }

    public void testUF(UFType type, String filename) throws IOException {
        BufferedReader br = new BufferedReader(new FileReader(filename));
        int N = Integer.parseInt(br.readLine());

        UF uf = getUF(type, N);
        String line = br.readLine();
        while (line != null) {
            String numbers[] = line.split(" ");
            int p = Integer.parseInt(numbers[0]);
            int q = Integer.parseInt(numbers[1]);
            if (!uf.connected(p, q)) {
                uf.union(p, q);
//                System.out.println(p + " " + q);
            }

            line = br.readLine();
        }

        br.close();
    }

    public static void main(String args[]) throws IOException {
        Main m = new Main();
        String filename = "F:\\hieult\\algorithms-1\\src\\com\\unionfind\\test.txt";
        long timeBefore;
        UFType type;

        type = UFType.QUICK_FIND_UF;
        timeBefore = System.currentTimeMillis();
        m.testUF(type, filename);
        System.out.println(type + " timing: " + (System.currentTimeMillis() - timeBefore) + "ms");

        type = UFType.QUICK_UNION_UF;
        timeBefore = System.currentTimeMillis();
        m.testUF(type, filename);
        System.out.println(type + " timing: " + (System.currentTimeMillis() - timeBefore) + "ms");

        type = UFType.QUICK_UNION_PATH_COMPRESSION_UF;
        timeBefore = System.currentTimeMillis();
        m.testUF(type, filename);
        System.out.println(type + " timing: " + (System.currentTimeMillis() - timeBefore) + "ms");

        type = UFType.WEIGHT_QUICK_UNION_UF;
        timeBefore = System.currentTimeMillis();
        m.testUF(type, filename);
        System.out.println(type + " timing: " + (System.currentTimeMillis() - timeBefore) + "ms");

        type = UFType.WEIGHT_QUICK_UNION_PATH_COMPRESSION_UF;
        timeBefore = System.currentTimeMillis();
        m.testUF(type, filename);
        System.out.println(type + " timing: " + (System.currentTimeMillis() - timeBefore) + "ms");
    }
}
