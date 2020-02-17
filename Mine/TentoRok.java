import java.io.*;
import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.List;

public class TentoRok {

    List<Photo> fotky;

    private void load(String fileName) {
        try (BufferedReader br = new BufferedReader(new FileReader(new File(fileName)))) {
            String line = br.readLine();
            String [] header = line.split(" ");

            while ((line = br.readLine()) != null) {

            }

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private List<Slide> kombinuj() {
        for (Photo p : fotky) {

        }

    }

    private int podobnost(Slide s1, Slide s2) {
        return 0;
    }

    private int novyEval (Slide s1, Slide s2) {
        int cislo1 = 0; //bitovy and;
        int cislo2 = 0; //pocet jednotiek v cislo1 - pocet jednotiek v slide.bit
        int cislo3 = 0; //pocet jednotiek v cislo1 - pocet jednotiek v s2.bit
        return Math.min(cislo1, Math.min(cislo2, cislo3));
    }

    private List<Slide> podobne (List<Slide> vertikalne) {
        ArrayList<Slide> vysl = new ArrayList<>();
        int naj = 0;
        int dvojicka = 0;
        boolean [] pouzite = new boolean[vertikalne.size()];
        for (int i = 0; i < vertikalne.size()-1; i++) {

            naj = 0;
            dvojicka = 0;
            for (int j = i + 1; j < vertikalne.size(); j++) {
                int nove = podobnost(vertikalne.get(i), vertikalne.get(j));
                if (nove > naj) {
                    naj = nove;
                    dvojicka = j;
                }
            }
            pouzite[i] = true;
            pouzite[dvojicka] = true;
            vysl.add(vertikalne.get(i));
            vysl.add(vertikalne.get(dvojicka));
        }
        return vysl;
    }

    private void save(List<String> results) {
        try (BufferedWriter writer = new BufferedWriter(new FileWriter("pizza.out"))) {

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
