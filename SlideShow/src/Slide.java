import java.util.ArrayList;
import java.util.HashSet;

import org.xml.sax.HandlerBase;

public class Slide {
	Photo f1, f2;

	public Slide(Photo f1) {
		this.f1 = f1;
		this.f2 = null;
	}

	public Slide(Photo f1, Photo f2) {
		this.f1 = f1;
		this.f2 = f2;
	}
	
   public boolean isOne() {
	   return f2 == null;
   }

   public String binaryTags() {
	   if (isOne()) {
		   return f1.vektor;
	   }
	   int len = f1.vektor.length();
	   StringBuilder sb = new StringBuilder();
	   for(int i = 0; i < len; i++) {
		   sb.append( ( f1.vektor.charAt(i) == '0' && f2.vektor.charAt(i) == '0') ? "0" : "1");
	   }
	   return sb.toString();	   
   }

   public String toString() {
	   if (isOne()) {
		   return ""+f1.ID;
	   } else {
		   return f1.ID + " " + f2.ID;
	   }
   }

   HashSet<String> allTags() {
	   HashSet<String> hs = new HashSet<>();
	   hs.addAll(f1.tags);
	   if (!isOne()) {
		   hs.addAll(f2.tags);
	   }
	   return hs;
	   /*
	   ArrayList<String> al = new ArrayList<>();
	   al.addAll(hs);
	   return al;
	   */
   }
}
