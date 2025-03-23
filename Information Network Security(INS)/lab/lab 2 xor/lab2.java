public class lab2 {
    public static void main(String[] args) {
        char a[] = {'d', 'a', 'r', 's', 'h', 'a', 'n'};
        System.out.print("main string: ");
        for (int i = 0; i < a.length; i++) {
            System.out.print(a[i]);
        }
        System.out.println();
        System.out.print("cyphertext: ");

        for (int i = 0; i < a.length; i++) {
            char d = (char) ((int) a[i] + 3);
            System.out.print(d);
        }
    }
}
