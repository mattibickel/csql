package csql.jdbc;
import java.sql.Connection;
import java.sql.Statement;
import java.sql.SQLException;
import java.sql.ResultSet;
import java.sql.SQLWarning;

public class JdbcSqlStatement extends JSqlError implements Statement, JSqlErrorType
{
    public boolean isClosed;
    public boolean isPrepared;
    public int rowsAffect;
    public JSqlStatement jniStmt;
    public JdbcSqlConnection conn;
    public JdbcSqlResultSet rs;

    JdbcSqlStatement( Connection con )
    {
        jniStmt = new JSqlStatement();
        jniStmt.alloc();
        conn = (JdbcSqlConnection) con;  
        jniStmt.setConnectionPtr( conn.getConnection().getPtr() ); 
        isClosed = false;
        isPrepared = false;
        rowsAffect = 0;
        rs = new JdbcSqlResultSet();
    }
    protected void finalize ()
    {
        try
        {
            if(!isClosed)
                close();
        }
        catch(SQLException e)
        {
            System.out.println(e);
        }
    }
    public void prepareInt(String query) throws SQLException
    {
        int rv = 0;
        if(isPrepared) 
	{
            rs.close();
            jniStmt.freeStmt();
            isPrepared = false;
        }
        rv = jniStmt.prepare(query);
        if( rv != 0 ) // 0 ->OK
        {
            throw getException(CSQL_PREPARE_ERR);
        }
        isPrepared = true;
    }
    public boolean executeInt() throws SQLException
    {
        if (!isPrepared) throw getException(CSQL_NOT_PREPARED);
        boolean isSelect = jniStmt.isSelect();
        rowsAffect = jniStmt.execute();
        if( rowsAffect < 0 )
            throw getException(CSQL_EXECUTE_ERR);
        if(conn.getAutoCommit())
            conn.commit();

        return(isSelect);
    }

    public void close() throws SQLException
    {
        if(isClosed) return;
        if(isPrepared)
        {
            rs.close();
            jniStmt.freeStmt();
            jniStmt.free();
        }
        isClosed = true;
        return;
    }
    public boolean execute (String query) throws SQLException
    {
        prepareInt(query);
        return(executeInt());
    }

    public ResultSet executeQuery(String query) throws SQLException
    {
        prepareInt(query);
        if( !jniStmt.isSelect() ) {
	    jniStmt.freeStmt();
            isPrepared = false;
            throw getException(CSQL_NOT_QUERY);
	}
	boolean hasResult = executeInt();

        rs.setStmt( this );
        return( rs );
    }
    public int executeUpdate (String query) throws SQLException
    {
        if(execute(query))
            throw getException(CSQL_NOT_UPDATE);
        return(rowsAffect);
    }
    public Connection getConnection() throws SQLException
    {
       return(conn);
    }
    public int getFetchDirection() throws SQLException
    {
        return(ResultSet.FETCH_FORWARD);
    }
    public int getFetchSize() throws SQLException
    {
        return 1;
    }
    public ResultSet getResultSet() throws SQLException
    {
        if(!jniStmt.isSelect())
            return (null);

        //TODO::Create ResultSet object
        return null;
    }
    public int getResultSetConcurrency() throws SQLException
    {
        return(ResultSet.CONCUR_READ_ONLY);
    }
    public int getResultSetHoldability() throws SQLException
    {
        return(ResultSet.CLOSE_CURSORS_AT_COMMIT);
    }
    public int getResultSetType()  throws SQLException
    {
        return(ResultSet.TYPE_FORWARD_ONLY);
    }
    public int getUpdateCount() throws SQLException
    {
        if(jniStmt.isSelect())
            return -1;
        return rowsAffect;
    }


    //Unsupported APIs
    public void addBatch(String sql) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public void cancel() throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public void clearBatch() throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public void clearWarnings() throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public boolean execute(String sql, int autoGeneratedKeys) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public boolean execute(String sql, int[] columnIndexes) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public boolean execute(String sql, String[] columnNames) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public int[] executeBatch() throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public int executeUpdate(String sql, int autoGeneratedKeys) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public int executeUpdate(String sql, int[] columnIndexes) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public int executeUpdate(String sql, String[] columnNames) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public ResultSet getGeneratedKeys() throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public int getMaxFieldSize() throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public int getMaxRows() throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public boolean getMoreResults() throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public boolean getMoreResults( int current) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public int getQueryTimeout() throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public SQLWarning getWarnings() throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public void setCursorName(String name) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public void setEscapeProcessing(boolean enable) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public void setFetchDirection(int direction) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public void setFetchSize(int rows) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public void setMaxFieldSize(int max) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public void setMaxRows(int maxRows) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }
    public void setQueryTimeout(int seconds) throws SQLException
    {
        throw getException(CSQL_NOT_SUPPORTED);
    }


}
