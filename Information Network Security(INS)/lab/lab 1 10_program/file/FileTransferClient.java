import java.io.*;
import java.net.*;

public class FileTransferClient {
    public static void main(String[] args) {
        final String SERVER_ADDRESS = "localhost";
        final int PORT = 12345;

        try (Socket socket = new Socket(SERVER_ADDRESS, PORT)) {
            System.out.println("Connected to the server!");

            // Receiving file
            File receivedFile = new File("received-file.txt");
            try (InputStream inputStream = socket.getInputStream();
                 BufferedOutputStream fileOutput = new BufferedOutputStream(new FileOutputStream(receivedFile))) {

                System.out.println("Receiving file...");
                byte[] buffer = new byte[4096];
                int bytesRead;

                while ((bytesRead = inputStream.read(buffer)) > 0) {
                    fileOutput.write(buffer, 0, bytesRead);
                }

                System.out.println("File received successfully: " + receivedFile.getAbsolutePath());
            }

        } catch (IOException e) {
            System.out.println("Client error: " + e.getMessage());
        }
    }
}
