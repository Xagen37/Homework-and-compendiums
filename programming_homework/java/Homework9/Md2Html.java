package md2html;

import md2html.markup.*;

import java.io.*;
import java.nio.charset.StandardCharsets;
import java.util.ArrayList;
import java.util.List;
import java.util.Stack;

public class Md2Html {

    private static final String HEADER = "h";
    private static final String STARSTRONG = "strong*";
    private static final String STRONG = "strong_";
    private static final String STAREMPHASIS = "emphasis*";
    private static final String EMPHASIS = "emphasis_";
    private static final String CODE = "code";
    private static final String STRIKEOUT = "strikeout";
    private static final String UNDERLINE = "underline";

    public static void main(String[] args) {
        String inputFileName = args[0];
        String outputFileName = args[1];

        Scanner sc = openInput(inputFileName, StandardCharsets.UTF_8.toString());
        if (sc == null) {
            return;
        }

        PrintWriter out = openWriter(outputFileName);
        if (out == null) {
            return;
        }

        Stack<Pair> state = new Stack<>();
        List<MarkdownUnit> text = new ArrayList<>();
        List<MarkdownUnit> temp = new ArrayList<>();
        int tempPtr = 0;
        StringBuilder lineToText = new StringBuilder();
        while (sc.hasNextLine() || !state.empty()) {
            if (lineToText.length() != 0) {
                tempPtr = insertText(temp, tempPtr, lineToText.toString());
                lineToText = new StringBuilder();
            }
            String line = "";
            if (sc.hasNextLine()) {
                line = sc.nextLine();
            }
            int startPoint = 0;
            if (!line.isEmpty()) {
                if (state.empty()) {
                    int cnt = 0;
                    while (line.charAt(startPoint) == '#') {
                        cnt++;
                        startPoint++;
                    }
                    if (Character.isWhitespace(line.charAt(startPoint))) {
                        state.push(new Pair(HEADER + cnt, tempPtr));
                        if (cnt != 0) {
                            startPoint++;
                        }
                    } else {
                        state.push(new Pair(HEADER + "0", tempPtr));
                        startPoint = 0;
                    }
                } else {
                    tempPtr = insertText(temp, tempPtr, "\n");
                }
                for (int i = startPoint; i < line.length(); i++) {
                    char toAdd = line.charAt(i);
                    switch (toAdd) {
                        case '`': {
                            if (state.peek().type.equals(CODE)) {
                                tempPtr = put(temp, tempPtr, CODE, state, lineToText.toString());
                                state.pop();
                            } else {
                                tempPtr = insertText(temp, tempPtr, lineToText.toString());
                                state.push(new Pair(CODE, tempPtr));
                            }
                            lineToText = new StringBuilder();
                            break;
                        }
                        case '*':
                        case '_': {
                            if ((i + 1) < line.length() && line.charAt(i + 1) == toAdd) {
                                if (state.peek().type.equals(STRONG) || state.peek().type.equals(STARSTRONG)) {
                                    tempPtr = put(temp, tempPtr, STRONG, state, lineToText.toString());
                                    state.pop();
                                } else {
                                    tempPtr = insertText(temp, tempPtr, lineToText.toString());
                                    if (toAdd == '_') {
                                        state.push(new Pair(STRONG, tempPtr));
                                    } else {
                                        state.push(new Pair(STARSTRONG, tempPtr));
                                    }
                                }
                                lineToText = new StringBuilder();
                                i++;
                            } else {
                                if ((state.peek().type.equals(EMPHASIS) && toAdd == '_') ||
                                        (state.peek().type.equals(STAREMPHASIS) && toAdd == '*')) {
                                    tempPtr = put(temp, tempPtr, EMPHASIS, state, lineToText.toString());
                                    lineToText = new StringBuilder();
                                    state.pop();
                                } else {
                                    tempPtr = insertText(temp, tempPtr, lineToText.toString());
                                    if (toAdd == '_') {
                                        state.push(new Pair(EMPHASIS, tempPtr));
                                    } else {
                                        state.push(new Pair(STAREMPHASIS, tempPtr));
                                    }
                                    lineToText = new StringBuilder();
                                }
                            }
                            break;
                        }
                        case '\\': {
                            if ((i + 1) < line.length() && (line.charAt(i + 1) == '*' || line.charAt(i + 1) == '_')) {
                                lineToText.append(line.charAt(i + 1));
                                i++;
                            }
                            break;
                        }
                        case '<': {
                            lineToText.append("&lt;");
                            break;
                        }
                        case '>': {
                            lineToText.append("&gt;");
                            break;
                        }
                        case '&': {
                            lineToText.append("&amp;");
                            break;
                        }
                        case '+': {
                            if ((i + 1) < line.length() && line.charAt(i + 1) == toAdd) {
                                i++;
                                if (state.peek().type.equals(UNDERLINE)) {
                                    tempPtr = put(temp, tempPtr, UNDERLINE, state, lineToText.toString());
                                    state.pop();
                                } else {
                                    tempPtr = insertText(temp, tempPtr, lineToText.toString());
                                    state.push(new Pair(UNDERLINE, tempPtr));
                                }
                                lineToText = new StringBuilder();
                                break;
                            }
                        }
                        case '-': {
                            if ((i + 1) < line.length() && line.charAt(i + 1) == toAdd) {    //else - fall-through
                                i++;
                                if (state.peek().type.equals(STRIKEOUT)) {
                                    tempPtr = put(temp, tempPtr, STRIKEOUT, state, lineToText.toString());
                                    state.pop();
                                } else {
                                    tempPtr = insertText(temp, tempPtr, lineToText.toString());
                                    state.push(new Pair(STRIKEOUT, tempPtr));
                                }
                                lineToText = new StringBuilder();
                                break;
                            }
                        }
                        default: {
                            lineToText.append(toAdd);
                            break;
                        }
                    }
                }
            } else {
                if (!state.empty()) {
                    Pair toClose = state.pop();
                    if (Character.toString(toClose.type.charAt(0)).equals(HEADER)) {
                        tempPtr = insertText(temp, tempPtr, lineToText.toString());
                        int rank = Character.getNumericValue(toClose.type.charAt(1));
                        if (rank == 0) {
                            text.add(new Paragraph(temp.subList(0, tempPtr)));
                        } else {
                            text.add(new Header(temp.subList(0, tempPtr), rank));
                        }
                        temp.clear();
                        tempPtr = 0;
                    } else {
                        switch (toClose.type) {
                            case STRONG: {
                                temp.add(toClose.pos, new Text("__"));
                                tempPtr++;
                                break;
                            }
                            case STARSTRONG: {
                                temp.add(toClose.pos, new Text("**"));
                                tempPtr++;
                                break;
                            }
                            case EMPHASIS: {
                                temp.add(toClose.pos, new Text("_"));
                                tempPtr++;
                                break;
                            }
                            case STAREMPHASIS: {
                                temp.add(toClose.pos, new Text("*"));
                                tempPtr++;
                                break;
                            }
                        }
                    }
                }
            }
        }

        StringBuilder toOut = new StringBuilder();
        for (MarkdownUnit unit : text) {
            unit.toHtml(toOut);
            toOut.append("\n");
        }
        out.print(toOut);

        sc.close();
        out.close();
    }

    //--------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------
    private static int put(List<MarkdownUnit> to, int toPtr, String type, Stack<Pair> state, String flush) {
        AbstractMarkdownUnit toAdd;
        if (type.equals(CODE)) {
            toAdd = new Code(
                    to.subList(
                            state.peek().pos, toPtr
                    )
            );
        } else if (type.equals(STRONG) || type.equals(STARSTRONG)) {
            toAdd = new Strong(
                    to.subList(
                            state.peek().pos, toPtr
                    )
            );
        } else if (type.equals(EMPHASIS) || type.equals(STAREMPHASIS)) {
            toAdd = new Emphasis(
                    to.subList(
                            state.peek().pos, toPtr
                    )
            );
        } else if (type.equals(UNDERLINE)) {
            toAdd = new Underline(
                    to.subList(
                            state.peek().pos, toPtr
                    )
            );
        } else {
            toAdd = new Strikeout(
                    to.subList(
                            state.peek().pos, toPtr
                    )
            );
        }
        toAdd.add(new Text(flush));
        if (state.peek().pos >= to.size()) {
            to.add(toAdd);
            return to.size();
        } else {
            to.set(state.peek().pos, toAdd);
            return state.peek().pos + 1;
        }
    }

    private static int insertText(List<MarkdownUnit> to, int toPtr, String toAdd) {
        if (toPtr >= to.size()) {
            to.add(
                    new Text(
                            toAdd
                    )
            );
            return to.size();
        } else {
            to.set(
                    toPtr, new Text(
                            toAdd
                    )
            );
            return toPtr + 1;
        }
    }

//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------
    private static Scanner openInput(String fileName, String encoding) {
        Scanner sc;
        try {
            sc = new Scanner(fileName, encoding);
        } catch (FileNotFoundException e) {
            System.out.println("Error: file not found!");
            return null;
        } catch (IOException e) {
            System.out.println("An IO error occurred:\n");
            e.printStackTrace();
            return null;
        }

        return sc;
    }

    private static PrintWriter openWriter(String fileName) {
        PrintWriter out;
        try {
            out = new PrintWriter(
                    new OutputStreamWriter(
                            new FileOutputStream(
                                    new File(fileName)
                            ),
                            StandardCharsets.UTF_8
                    )
            );
        } catch (IOException e) {
            System.out.println("An IO error occurred:\n");
            e.printStackTrace();
            return null;
        }

        return out;
    }

//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------
    private static class Pair {
        String type;
        int pos;

        Pair(String type, int pos) {
            this.type = type;
            this.pos = pos;
        }
    }
}