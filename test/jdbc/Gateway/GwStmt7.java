//delete tuple with WHERE clause having params (DELETE FROM t1 WHERE f1=?AND f9=?) using gateway
import java.sql.*;
/**
 *
 * @author bijaya
 */
public class GwStmt7 {
public static void main(String[] arg)
    {
        try
        {
            Class.forName("csql.jdbc.JdbcSqlDriver");
            Connection con=DriverManager.getConnection("jdbc:gateway","root","manager");
            Statement cStmt=con.createStatement();
            PreparedStatement stmt=null,selStmt=null;
            stmt=con.prepareStatement("INSERT INTO t1 VALUES(?,?,?,?,?,?,?,?);");
            int ret=0;
            for(int i=0;i<10;i++)
            {
                stmt.setInt(1,i);
                stmt.setShort(2,(short)(i+1));
//                stmt.setByte(3,(byte)(i+2));
                stmt.setLong(3,(long)i);
                stmt.setFloat(4,(float)1000+i);
                stmt.setString(5, String.valueOf("Cache"+i));
                stmt.setDate(6,Date.valueOf("2008-03-21"));
                stmt.setTime(7,Time.valueOf("18:00:00"));
                stmt.setTimestamp(8,Timestamp.valueOf("2008-03-21 18:00:00"));
                ret=stmt.executeUpdate();
                if(ret!=1) break;
            }
            stmt.close();
            con.commit();
            selStmt=con.prepareStatement("Select * from t1");
            ResultSet rs=null;
            rs=selStmt.executeQuery();
            while(rs.next())
            {
                System.out.println("Tuple value is " + rs.getInt(1) + " "+
                                                        rs.getShort(2) + " "+
                                                        rs.getLong(3) + " "+
                                                        rs.getFloat(4) + " "+
                                                        rs.getString(5) + " "+
                                                        rs.getDate(6) + " "+
                                                        rs.getTime(7) + " "+
                                                        rs.getTimestamp(8) + " "
                                                        );

            }
            rs.close();
            con.commit();
            ret=0;
            stmt=con.prepareStatement("DELETE FROM t1 WHERE f1=? AND f9=?;");
            for(int i=0;i<10;i++)
            {
                stmt.setInt(1,3);
                stmt.setTimestamp(2,Timestamp.valueOf("2008-03-21 18:00:00"));
                ret=stmt.executeUpdate();
                if(ret!=1) break;
            }
            stmt.close();
            con.commit();
            selStmt=con.prepareStatement("Select * from t1");
            rs=null;
            rs=selStmt.executeQuery();
            System.out.println();
            while(rs.next())
            {
                System.out.println("Tuple value is " + rs.getInt(1) + " "+
                                                        rs.getShort(2) + " "+
                                                        rs.getLong(3) + " "+
                                                        rs.getFloat(4) + " "+
                                                        rs.getString(5) + " "+
                                                        rs.getDate(6) + " "+
                                                        rs.getTime(7) + " "+
                                                        rs.getTimestamp(8) + " "
                                                        );

            }
            rs.close();
            con.commit();
            con.close();
       }catch(Exception e) {
            System.out.println("Exception in Test: "+e);
            e.printStackTrace();
        }
    }

}
