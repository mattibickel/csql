//Try to connect with connectstring "jdbc:csql" and give empty properties object. It should fail.
import java.sql.*;
public class ConnTest8 
{
    public static void main(String[] args) 
    {
       try
       {
           Class.forName("csql.jdbc.JdbcSqlDriver");
           Connection con = DriverManager.getConnection("jdbc:csql://localhost:5678", null, null);
           if (con != null) {con.close(); System.exit(1);}
        }catch(Exception e) {
            System.out.println("Exception in Test: "+e.getMessage());
            e.getStackTrace();
            System.exit(0);
       }
    }
}
