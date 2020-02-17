import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintStream;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.Random;
import java.util.Scanner;

public class SlideShow {
	static Random rnd = new Random();
	
	public static void main(String[] args) throws FileNotFoundException {
		String run = "8";
		String mata = "mata";
		String prefix = "";
		ArrayList<String> inputs = new ArrayList<>();
		//inputs.add("a_example");
		//inputs.add("b_lovely_landscapes");
		//inputs.add("c_memorable_moments");
		//inputs.add("d_pet_pictures");
		inputs.add("e_shiny_selfies");
		for (String input : inputs) {
			String infileName = prefix + input + ".txt";
			String outfileName = prefix + run + "/" + input + ".out";
			String matafileName = prefix + mata + "/" + input + ".txt";
			HashSet<String> allTags = new HashSet<>();
			ArrayList<Photo> photos = new ArrayList<>();
			Scanner sc = new Scanner(new File(infileName));
			int N = sc.nextInt();
			sc.nextLine();
			//System.out.println(N);
			for(int i = 0; i < N; i++) {
				String line = sc.nextLine();
				//System.out.println(line);
				String a[] = line.split(" ");
				String orient = a[0];
				Integer pocetTag = Integer.parseInt(a[1]);
				ArrayList<String> tags = new ArrayList<>();
				for (int j=0; j < pocetTag; j++) {
					tags.add(a[2+j]);
				}
				Photo f = new Photo(orient.equals("H"), i, tags);
				allTags.addAll(tags); //pozbieraj tagy jednej fotky
				photos.add(f);
				//System.out.println(i +","+tags);
			}
			sc.close();
			//nacitajMatu(matafileName, photos);
			
			System.out.println("vstupny file: " + input);
			//System.out.println("vsetkych tagov je " + allTags.size());

			//System.out.println("vsetkych fotiek je " + photos.size());
			ArrayList<Slide> slides = gener(photos);
			
			int e = evalInt(slides);
			System.out.println("vysledna funkcia = " + e);
			
			ArrayList<Slide> newSlides = preusporiadaj(slides);
			int newe = evalInt(newSlides);
			System.out.println("\nlepsia funkcia = " + newe);

			new File(prefix + run).mkdir();
			PrintStream ps = new PrintStream(outfileName);
			ps.println(slides.size());
			for(Slide s:newSlides) {
				ps.println(s);
			}
			ps.close();		
		}
	}
	
	static void nacitajMatu(String fileName, ArrayList<Photo> photos)  {
		try(Scanner sc = new Scanner(new File(fileName))) {
			for (int i = 0; i < photos.size(); i++) {
				String line = sc.nextLine();
				//System.out.println(line.length());
				photos.get(i).vektor = line;
			}
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}
	}
	
	static int evalVektor(Slide s1, Slide s2 ) {
		String s1tags = s1.binaryTags();
		String s2tags = s2.binaryTags();
		StringBuilder bitovyAnd = new StringBuilder();
		for(int i = 0; i < s1tags.length(); i++) {
			bitovyAnd.append( ( s1tags.charAt(i) == '1' && s2tags.charAt(i) == '1') ? "1" : "0");
		}
		int cislo1 = pocetJednotiek(bitovyAnd.toString());
		int cislo2 = pocetJednotiek(s1tags) - cislo1;
		int cislo3 = pocetJednotiek(s2tags) - cislo1;
		
		int e = Math.min(cislo1, Math.min(cislo2, cislo3));
		//ystem.out.print(e); System.out.println();
		return e;
	}
	
	static int pocetJednotiek(String s) {
		int pocet = 0;
		for(int i = 0; i < s.length(); i++) {
			if (s.charAt(i) == '1') pocet++; 
		}
		return pocet;
	}

	static int eval(Slide s1, Slide s2 ) {
		HashSet<String> tags1 = s1.allTags();
		HashSet<String> tags2 = s2.allTags();
		int pocet = 0;
		for(String t : tags1) {
			if (tags2.contains(t))
				pocet++;
		}
		int e = Math.min(pocet, Math.min(tags1.size() - pocet, tags2.size() - pocet));
		return e;
	}
	
	static ArrayList<Integer> eval(ArrayList<Slide>slides ) {
		ArrayList<Integer> al = new ArrayList<>();
		for (int i = 0; i <slides.size()-1; i++ ) {
			al.add(eval(slides.get(i), slides.get(i+1)));
		}
		return al;
	}

	static int evalInt(ArrayList<Slide>slides ) {
		int e = 0;
		for (int i = 0; i <slides.size()-1; i++ ) {
			e += eval(slides.get(i), slides.get(i+1));
		}
		return e;
	}
	
	static ArrayList<Slide> gener(ArrayList<Photo> photos) {
		Photo lastVert = null;
		ArrayList<Slide> slides = new ArrayList<>();
		for(int i = 0; i < photos.size(); i++) {
			Photo f = photos.get(i);
			if (f.horizOr) {
				slides.add(new Slide(f));
			} else {
				if (lastVert != null) {
					slides.add(new Slide(lastVert, f));
					lastVert = null;
				} else {
					lastVert = f;
				}
			}
		}
		return slides;
	}

	static private ArrayList<Slide> preusporiadaj(ArrayList<Slide> slides) {
	    ArrayList<Slide> vysl = new ArrayList<>();
	    boolean [] pouzite = new boolean[slides.size()];
	    for (int i = 0; i < slides.size()-1; i++) {
	    	if (pouzite[i]) continue;
	    	if (i % 1000 == 0) {
	    		System.out.print(i + ",");
	    	}
			int naj = 0;
			int dvojicka = -1;

	        for (int k = 0; k < Math.min(2000, slides.size()); k++) {
				int j = rnd.nextInt(slides.size());
				while (i == j || pouzite[j]) {
					j = rnd.nextInt(slides.size());
				}

	        //for (int j = i + 1; j < Math.min(i + 20000, slides.size()); j++) {
	        //for (int j = i + 1; j < vertikalne.size(); j++) {
	        	if (pouzite[j]) continue;
	            int nove = eval(slides.get(i), slides.get(j));
	            //int nove = evalVektor(vertikalne.get(i), vertikalne.get(randomIndex));
	            if (nove >= naj) {
	                naj = nove;
	                dvojicka = j;
	            }
	        }
	        pouzite[i] = true;
	        vysl.add(slides.get(i));
	        if (dvojicka != -1) {
	        	pouzite[dvojicka] = true;
	        	vysl.add(slides.get(dvojicka));
	        }
	        //System.out.println(vertikalne.get(i) +", "+vertikalne.get(dvojicka));
	    }
	    return vysl;
	}
	
}
