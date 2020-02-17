public class Main {
    public static void main(String[] args) {
        Ja lukas = Ja.dajMa();
        BorovanskySingleton boro = BorovanskySingleton.dajPetra();
        KamaratPeter k = (KamaratPeter) boro;
        PedagogBorovansky p = (PedagogBorovansky) boro;

        System.out.println(k.getClass());
        System.out.println(p.getClass());

    }
}

class Ja {
    private static Ja lukas = null;

    private Ja () { }

    public static Ja dajMa() {
        if (lukas == null) lukas = new Ja();
        return lukas;
    }

    public void pozdrav(BorovanskySingleton b) {
        if (b instanceof PedagogBorovansky) {
            System.out.println("Dobry den, pan Borovansky");
        } else if (b instanceof KamaratPeter) {
            System.out.println("Nazdar Peto!!!");
        }
    }
}

class PedagogBorovansky { }

class KamaratPeter extends PedagogBorovansky { }

class BorovanskySingleton extends KamaratPeter {
    private static BorovanskySingleton peter = null;

    private BorovanskySingleton () { }

    public static BorovanskySingleton dajPetra() {
        if (peter == null) peter = new BorovanskySingleton();
        return peter;
    }
}

