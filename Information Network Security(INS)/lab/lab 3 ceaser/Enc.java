import java.util.*;


public class Enc {
public static void main(String[] args) 
{ 
    Scanner scan =new Scanner(System.in);
    System.out.println("Enter string: ");
    String a = scan.nextLine();
    
    Encryption(a);
    
}
public static void Encryption(String a)
{
    Scanner scan =new Scanner(System.in);
    System.out.println("enter key");
    int keey;
    if(scan.hasNextInt()) {
        keey = scan.nextInt();
    } else {
        System.out.println("Invalid input. Please enter an integer.");
        return; // Exit the method if input is invalid
    }

    System.out.println("ciper:");

    char d;
    for(int i=0;i<a.length();i++){

        d= (char)((int)a.charAt(i)+keey);
        System.out.print(d);
    }
}
}
