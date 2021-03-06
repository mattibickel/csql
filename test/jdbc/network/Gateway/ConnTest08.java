//Open the connection through jdbc:gateway://localhost:5678 and then call isClosed(). It should return false.
//Close the connection jdbc:gateway://localhost:5678 and then call isClosed(). It should return true.

import java.sql.*;
public class ConnTest08 
{
    public static void main(String[] args) 
    {
       try
       {
           Class.forName("csql.jdbc.JdbcSqlDriver");
           Connection con = DriverManager.getConnection("jdbc:gateway://localhost:5678", "root", "manager");
	   if ( con == null )
		   System.exit(1);
	   if(con.isClosed()) System.exit(1);
           con.close();
	   if(!con.isClosed()) System.exit(1);
        }catch(Exception e) {
            System.out.println(e.getMessage());
            e.getStackTrace();
            System.exit(1);
       }
    }
}
