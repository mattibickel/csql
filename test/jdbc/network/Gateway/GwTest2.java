//Donot start the server .Connect with connectstring "jdbc:gateway://localhost:5678" and null for username and password. It should fail
import java.sql.*;
/**
 *
 * @Author : Nihar
 */
public class GwTest2 {
     public static void main(String[] args)
    {
       try
       {
           Class.forName("csql.jdbc.JdbcSqlDriver");
           Connection con = DriverManager.getConnection("jdbc:gateway://localhost:5678", null, null);
           if (con != null) {con.close(); System.exit(1);}
        }catch(Exception e) {
            System.out.println("Exception in Test: "+e.getMessage());
            e.getStackTrace();
            System.exit(0);
       }
    }

}
