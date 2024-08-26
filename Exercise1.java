/* package codechef; // don't place package name! */

import java.util.Scanner;

/* Name of the class has to be "Main" only if the class is public. */
class Exercise1 {
    /** A simple static string for HTML & table header. */
    private static final String HTMLHeader = 
        "<!DOCTYPE html>\n"
        + "  <html>\n"
        + "    <head>\n"
        + "     <title>CSE-278: Exercise 1</title>\n"
        + "    </head>\n"
        + "  <body>\n"
        + "    <table border=1>";
        
    /** A simple static string to print HMTL footer. */
    private static final String HTMLFooter =
        "    </table>\n"
        + "  </body>\n"
        + "</html>";
        
    public static void main(String[] args) {
        System.out.println(HTMLHeader);
        Scanner keyboard = new Scanner(System.in);
        String prevLine = "";
        while (keyboard.hasNextLine()) {
            String line = keyboard.nextLine();
            if (line.isEmpty() && !prevLine.isEmpty()) {
                System.out.println("      <tr><td>" + prevLine + "</td></tr>");
            }
            prevLine = line;
        }
        // Finally handle last line (if file has no trailing blank lines)
        if (!prevLine.isEmpty()) {
            System.out.println("      <tr><td>" + prevLine + "</td></tr>");
        }
        System.out.println(HTMLFooter);
    }
}
