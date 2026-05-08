import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.math.BigInteger;

public class D_simple {
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringBuilder out = new StringBuilder();

        int T = Integer.parseInt(in.readLine().trim());
        for (int t = 0; t < T; t++) {
            BigInteger x = new BigInteger(in.readLine().trim());
            out.append(x.shiftLeft(1)).append('\n');
        }

        System.out.print(out);
    }
}
