import java.util.ArrayList;

public class Photo {

	boolean horizOr;
	ArrayList<String> tags;
	int ID;
	String vektor;
	
	public Photo(boolean horizOr, int ID, ArrayList<String> tags) {
		super();
		this.horizOr = horizOr;
		this.tags = tags;
		this.ID = ID;
	}

	@Override
	public String toString() {
		return "Photo [horizOr=" + horizOr + ", ID=" + ID + ", tags=" + tags + "]";
	}
	
}
