import edu.princeton.cs.algs4.StdDraw;
import edu.princeton.cs.algs4.StdRandom;
import edu.princeton.cs.algs4.StdStats;
import edu.princeton.cs.algs4.WeightedQuickUnionUF;

public class Percolation {
    /**
     * (2-1) * 4  + 3 = 7
     * (3-1) * 4  + 4 = 12
     * (2-1) * 4 + 4 = 8
     * 2-1 * 4 + 1 = 5
     * 4x4
     * 5x5
     * 5x1 = (5-1)*5 + 1 = 21
     *        0
     *  1   2  3  4 5
     *  6   7  8  9 10
     *  11  12 13 14 15
     *  16 17 18 19 20
     *  21 22 23 24 25
     *       26
     */
    private  WeightedQuickUnionUF grid;
    private boolean isOpen[][];
    private boolean isFull[][];
    private int gridSize = 0;

    private void validate(int row, int col) throws IllegalArgumentException {
        if (row < 1 || col < 1 || row > gridSize || col > gridSize) {
            throw new IllegalArgumentException();
        }
    }

    // create n-by-n grid, with all sites blocked
    public Percolation(int n) {
        if (n <= 0) {
            throw new IllegalArgumentException("n(" + n + ") <= 0");
        }

        gridSize = n;
        grid = new WeightedQuickUnionUF((n * n) + 2);
        isOpen = new boolean[n][n];
        isFull = new boolean[n][n];

        for (int i=0; i<n; ++i) {
            for (int j=0; j<n; ++j) {
                isOpen[i][j] = false;
                isFull[i][j] = false;
            }
        }

        int lastRowLoc = ((n-1) * n) + 1;
        for (int i=1; i<=n; ++i) {
            grid.union(0, i);
            grid.union(lastRowLoc + n, lastRowLoc + (i-1));
        }

    }

    // open site (row, col) if it is not open already
    public    void open(int row, int col) {
        validate(row, col);

        isOpen[row-1][col-1] = true;

        int loc = ((row-1) * gridSize) + col;
        // connect left
        if ((col - 1) >= 1 && isOpen(row, col-1) == true) {
            grid.union(loc, loc - 1);
        }
        // connect right
        if (col + 1 <= gridSize && isOpen(row, col+1) == true) {
            grid.union(loc, loc + 1);
        }
        // connect top
        if (row-1 >= 1 && isOpen(row-1, col) == true) {
            grid.union(loc, loc - gridSize);
        }
        // connect bottom
        if (row+1 <= gridSize && isOpen(row+1, col) == true) {
            grid.union(loc, loc + gridSize);
        }

        // Check if it's connected to first virtual node or not
        if (grid.connected(0, loc)) {
            isFull[row-1][col-1] = true;
        }
    }

    // is site (row, col) open?
    public boolean isOpen(int row, int col) {
        validate(row, col);

        return isOpen[row-1][col-1];
    }

    // is site (row, col) full?
    public boolean isFull(int row, int col) {
        validate(row, col);

        return isFull[row-1][col-1];
    }

    // number of open sites
    public     int numberOfOpenSites() {
        int count = 0;
        for (int row=1; row<=gridSize; ++row) {
            for (int col=1; col<=gridSize; ++col)
                if (isOpen(row, col)) {
                    count++;
                }
        }

        return count;
    }

    // does the system percolate?
    public boolean percolates() {
        int lastRowLoc = ((gridSize-1) * gridSize) + 1;
        for (int col=1; col<=gridSize; ++col, ++lastRowLoc) {
            if (grid.connected(lastRowLoc, 0))
                return true;
        }

        return false;
    }

    // draw the n-by-n boolean matrix to standard draw
    public static void show(boolean[][] a, boolean which) {
        int n = a.length;
        StdDraw.setXscale(-1, n);
        StdDraw.setYscale(-1, n);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (a[i][j] == which)
                    StdDraw.filledSquare(j, n-i-1, 0.5);
    }

    // test client (optional)
    public static void main(String[] args) {
        Percolation per = new Percolation(5);
        per.open(1, 1);
        per.open(1, 2);
        per.open(1, 4);
        per.open(2, 4);
        per.open(3, 2);
        per.open(3, 4);
        per.open(3, 5);
        per.open(4, 1);
        per.open(4, 3);
        per.open(5, 1);
        per.open(5, 2);
        per.open(5, 4);
        per.open(5, 5);

        per.show(per.isOpen, false);
    }
}
