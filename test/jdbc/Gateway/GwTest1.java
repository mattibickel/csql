 // Connect with connectstring "jdbc:gateway" and give correct "user" and "password" in properties object.
 //It should pass.when csqlserver is not runnig
import java.sql.*;

/**
 *
 * @author bijaya
 */
public class GwTest1 {
 public static void main(String[] args)
    {
       try
       {
           Class.forName("csql.jdbc.JdbcSqlDriver");
           Connection con = DriverManager.getConnection("jdbc:gateway", "root", "manager");
          if ( con == null )
          {
              System.out.println("Test Case Fail");
              System.exit(1);
          }
           System.out.println("Test Case Passed");
           con.close();
           System.exit(0);
        }catch(Exception e) {
            System.out.println("Exception in Test: "+e);
            e.getStackTrace();
            System.exit(1);
       }
    }

}
