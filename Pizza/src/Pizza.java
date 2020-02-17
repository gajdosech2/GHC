import java.io.*;
import java.util.ArrayList;
import java.util.List;

public class Pizza {
    char[][] P;
    int rowCount, columnCount, minIngredient, maxArea;

    public static void main(String[] args) {
        Pizza p = new Pizza();
        p.load("a_example.in");
        p.solve();
    }

    private void load(String fileName) {
        try (BufferedReader br = new BufferedReader(new FileReader(new File(fileName)))) {
            String line = br.readLine();
            String [] header = line.split(" ");
            rowCount = Integer.parseInt(header[0]);
            columnCount = Integer.parseInt(header[1]);
            minIngredient = Integer.parseInt(header[2]);
            maxArea = Integer.parseInt(header[3]);
            P = new char[rowCount][columnCount];
            int i = 0;
            while ((line = br.readLine()) != null) {
                for (int j = 0; j < columnCount; j++) {
                    P[i][j] = line.charAt(j);
                }
                i++;
            }
            if (i != rowCount) {
                System.out.println("Number of rows error!");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }


    private void solve() {
        List<Slice> results = new ArrayList<>();

        for (int r = 0; r < rowCount; r++) {
            int beg = 0;
            int end = 0;
            int mushroomCount = 0;
            int tomatoCount = 0;

            while (end < columnCount) {

                if (P[r][end] == 'T') {
                    tomatoCount++;
                } else if (P[r][end] == 'M') {
                    mushroomCount++;
                }
                end++;

                if (end - beg > maxArea) {
                    if (P[r][beg] == 'T') {
                        tomatoCount--;
                    } else if (P[r][beg] == 'M') {
                        mushroomCount--;
                    }
                    beg++;
                }

                if (end - beg <= maxArea && mushroomCount >= minIngredient && tomatoCount >= minIngredient) {
                    results.add(new Slice(r, beg, r, end-1));
                    beg = end;
                    mushroomCount = 0;
                    tomatoCount = 0;
                }
            }
        }
        save(results);
    }

    private void save(List<Slice> results) {
        try (BufferedWriter writer = new BufferedWriter(new FileWriter("pizza.out"))) {
            writer.write(results.size() + "");
            writer.newLine();
            for (Slice slice : results) {
                writer.write(slice.toString());
                writer.newLine();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void printPizza() {
        for (int i = 0; i < rowCount; i++) {
            for (int j = 0; j < columnCount; j++) {
                System.out.print(P[i][j]);
            }
            System.out.println();
        }
    }
}

class Slice {
    int r1, c1, r2, c2;

    public Slice(int r1, int c1, int r2, int c2) {
        this.r1 = r1;
        this.c1 = c1;
        this.r2 = r2;
        this.c2 = c2;
    }

    @Override
    public String toString() {
        return r1 + " " + c1 + " " + r2 + " " + c2;
    }
}
