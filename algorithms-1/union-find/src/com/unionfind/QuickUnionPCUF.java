package com.unionfind;

public class QuickUnionPCUF implements UF {
    private int id[];

    private int root(int i) {
        while(i != id[i]) {
            id[i] = id[id[i]];
            i = id[i];
        }

        return i;
    }

    public QuickUnionPCUF(int N) {
        id = new int[N];
        for (int i=0; i<N; ++i) {
            id[i] = i;
        }
    }

    public boolean connected(int p, int q) {
        return root(p) == root(q);
    }

    public void union(int p, int q) {
        int rootp = root(p);
        int rootq = root(q);
        id[rootp] = rootq;
    }
}