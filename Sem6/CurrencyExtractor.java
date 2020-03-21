import java.io.*;
import java.net.URL;
import java.util.Scanner;

public class CurrencyExtractor {

    static Double getEuroRate() {
        String parsedRate = null;
        try {
            String parsedFile = new Scanner(new URL("http://www.profinance.ru/currency_eur.asp").openStream(), "UTF-8").useDelimiter("\\A").next();
            String previousString = "<td>Евро</td>\n" + "\t\t\t\t\t<td>";
            int index = parsedFile.lastIndexOf(previousString) + previousString.length();
            parsedRate = parsedFile.substring(index, index + 7);
        } catch (IOException e) {
            throw new UncheckedIOException(e);
        }
        return Double.parseDouble(parsedRate);
    }

    static void saveRateToFile(Double rate) {
        try(BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter("rate.txt"))) {
            bufferedWriter.write(rate.toString());
        } catch (IOException e) {
            throw new UncheckedIOException(e);
        }
    }
    public static void main(String[] args) {
        saveRateToFile(getEuroRate());
    }

}
