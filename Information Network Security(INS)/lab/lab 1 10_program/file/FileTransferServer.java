import java.io.*;
import java.net.*;

public class FileTransferServer {
    public static void main(String[] args) {
        final int PORT = 12345;

        try (ServerSocket serverSocket = new ServerSocket(PORT)) {
            System.out.println("Server is running and waiting for a connection...");
            Socket clientSocket = serverSocket.accept();
            System.out.println("Client connected!");

            // File to send
            File fileToSend = new File("file-to-send.txt");
            if (!fileToSend.exists()) {
                System.out.println("File does not exist.");
                return;
            }

            // Sending file
            try (BufferedInputStream fileInput = new BufferedInputStream(new FileInputStream(fileToSend));
                 OutputStream outputStream = clientSocket.getOutputStream()) {

                System.out.println("Sending file: " + fileToSend.getName());
                byte[] buffer = new byte[4096];
                int bytesRead;

                while ((bytesRead = fileInput.read(buffer)) > 0) {
                    outputStream.write(buffer, 0, bytesRead);
                }

                System.out.println("File sent successfully!");
            }

        } catch (IOException e) {
            System.out.println("Server error: " + e.getMessage());
        }
    }
}
