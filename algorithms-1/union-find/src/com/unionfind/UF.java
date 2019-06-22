package com.unionfind;

public interface UF {
    boolean connected(int p, int q);
    void union(int p, int q);
}
