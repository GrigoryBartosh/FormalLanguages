package ru.spbau.gbarto;

import dk.brics.automaton.Automaton;
import dk.brics.automaton.RegExp;

import java.io.*;

public class Main {
    /**
     * s = ' '
     * m = '-'
     * p = '+'
     * t = ';'
     * z = ','
     * d = '.'
     * u = '['
     * v = ']'
     * x = '('
     * y = ')'
     */

    public static void main(String[] args) {
        String cp = "(1|2|3|4|5|6|7|8|9)";
        String c = "(0|" + cp + ")";
        String np = "(" + cp + c + "*)";
        String n = "(" + "m" + np + "|0|" + np + ")";
        String s = "(s*)";
        String ns = "(" + s + n + s + ")";
        String l = "(u(" + ns + "t)*" + ns + "|" + s + "v)";

        String ident = "(i)";
        String idents = "(" + s + ident + s + ")";
        String ls = "(" + s + l + s + ")";
        String element = "(" + ns + "|" + ls + "|" + idents + ")";
        String cortege = "(x(" + element + "z)*" + element + "|" + s + "y)";

        String n0 = "(0|" + np + ")";
        String nmp = "(m" + np + "|p" + np + "|" + np + ")";
        String flt = "(" +
                        n + "|" +
                        "d" + n0 + "|" +
                        "e" + nmp + "|" +
                        n + "d" + n0 + "|" +
                        n + "e" + nmp + "|" +
                        "d" + n0 + "e" + nmp + "|" +
                        n + "d" + n0 + "e" + nmp +
                     ")";

        RegExp r = new RegExp(flt);
        Automaton a = r.toAutomaton();
        a.determinize();
        a.minimize();

        try (Writer writer = new BufferedWriter(
                new OutputStreamWriter(
                        new FileOutputStream("2d.txt"), "utf-8"))) {
            writer.write(a.toString());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
