echo select sales_order_details.productno,description from sales_order_details,sales_order,product_master,client_master where product_master.productno=sales_order_details.productno and sales_order.orderno=sales_order_details.orderno and client_master.clientno=sales_order.clientno and client_master.name='Ivan Bayross';
select sales_order_details.productno,description from sales_order_details,sales_order,product_master,client_master where product_master.productno=sales_order_details.productno and sales_order.orderno=sales_order_details.orderno and client_master.clientno=sales_order.clientno and client_master.name='Ivan Bayross';