package info.kgeorgiy.ja.sofrygin.walk;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStream;
import java.nio.file.FileAlreadyExistsException;
import java.nio.file.Files;
import java.nio.file.InvalidPathException;
import java.nio.file.Path;

public class Walk {
    public static void main(String[] args) {
        if (args == null) {
            System.err.println("Expected  not null arguments");
            return;
        } else if (args.length != 2) {
            System.err.println("Wrong number of arguments. Expected 2, got " + args.length);
            return;
        } else if (args[0] == null) {
            System.err.println("Input file name is null");
            return;
        } else if (args[1] == null) {
            System.err.println("Output file name is null");
            return;
        }

        Path inputFilePath;
        Path outputFilePath;
        try {
            inputFilePath = Path.of(args[0]);
        } catch (InvalidPathException e) {
            System.err.println("Input file name is not valid");
            return;
        }

        try {
            outputFilePath = Path.of(args[1]);
        } catch (InvalidPathException e) {
            System.err.println("Output file name is not valid");
            return;
        }


        Path outputDirectories = outputFilePath.getParent();
        if (outputDirectories != null) {
            try {
                Files.createDirectories(outputDirectories);
            } catch (FileAlreadyExistsException e) {
                System.err.println("Path to output file contains non-directories");
                return;
            } catch (IOException e) {
                System.err.println("Error while creating path to output file");
                return;
            }
        }

        try (BufferedWriter out = Files.newBufferedWriter(outputFilePath)) {
            try (BufferedReader in = Files.newBufferedReader(inputFilePath)) {
                processFiles(in, out);
            } catch (IOException e) {
                System.err.println("Input file can't be opened");
            }
        } catch (IOException e) {
            System.err.println("Output file can't be opened or created");
        }
    }

    private static void processFiles(BufferedReader in, BufferedWriter out) {
        try {
            String fileName;
            while ((fileName = in.readLine()) != null) {
                long hash;
                try {
                    Path filePath = Path.of(fileName);
                    hash = processFile(filePath);
                } catch (InvalidPathException e) {
                    hash = 0;
                }

                try {
                    out.write(String.format("%016x", hash) + " " + fileName + "\n");
                } catch (IOException e) {
                    System.err.println("Error while writing to output file: " + e.getMessage());
                    return;
                }
            }
        } catch (IOException e) {
            System.err.println("Error while reading input file: " + e.getMessage());
        }
    }

    private static long processFile(Path filePath) {
        long hash = 0;
        try (InputStream stream = Files.newInputStream(filePath)) {
            byte[] s = new byte[1024];
            int readCount = 0;
            while ((readCount = stream.readNBytes(s, 0, s.length)) != 0) {
                hash = countHash(s, readCount, hash);
            }
        } catch (IOException e) {
            hash = 0;
        }

        return hash;
    }

    private static long countHash(final byte[] s, final int length, long prev) {
        final int BITS = 64;
        final int EIGHTH = BITS / 8;
        final int QUARTERS = BITS * 3 / 4;
        final long LEFTBITS = 0xFFFF_FFFF_FFFF_FFFFL << (BITS - EIGHTH);

        long high;
        for (int i = 0; i < length; i++) {
            prev = (prev << EIGHTH) + (s[i] & 0xff);
            if ((high = prev & LEFTBITS) != 0) {
                prev = prev ^ (high >> QUARTERS);
                prev = prev & ~high;
            }
        }

        return prev;
    }
}
