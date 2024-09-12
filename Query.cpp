#ifndef Query_H_
#define Query_H_
#include "HSERVER.h"

DATABASE::DATABASE() { 
    std::cout<<"생성자 생성\n";
            
	try {
		sql::Driver* driver = sql::mariadb::get_driver_instance();
		sql::SQLString url("jdbc:mariadb://10.10.21.116:3306/IMAGE_SOLUTION");
		sql::Properties properties({{"user", "OPERATOR"}, {"password", "1234"}});
		conn = std::unique_ptr<sql::Connection>(driver->connect(url, properties));
		
		// First query: Count users
		std::unique_ptr<sql::Statement> stmnt(conn->createStatement());
	}
	catch(sql::SQLException & e) {
		std::cerr << "Error Connecting to MariaDB Platform: " << e.what() << std::endl;
	}
}

void DATABASE::Result_save(std::string result,std::string ID)
{
	std::cout << "결과 저장\n";
	try
	{
		std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("UPDATE MASK SET M_Result = ? WHERE M_Result = '검사중' and M_NAME = ?"));
		stmnt->setString(1,result);
		stmnt->setString(2,ID);
		stmnt->executeUpdate();
	}
	catch (sql::SQLDataException &e)
	{	
		std::cout <<"결과 저장 오류\n";
		std::cerr << e.what() << std::endl;
	}
}

int DATABASE::Recieve_image(std::string file_name)
{	int check = 0;
	std::cout <<"Mask 저장\n";
	try
	{
		std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("INSERT INTO MASK (NO, M_TIME, M_NAME, M_RESULT) VALUES (DEFAULT, DEFAULT, ?, DEFAULT)"));
		stmnt->setString(1,file_name);
		stmnt->executeQuery();
		check = 1; // 저장 성공
	}
	catch(const std::exception& e)
	{
		std::cout <<"Mask 저장 error\n";
		std::cerr << e.what() << '\n';
	}

	return check;
	
}
std::string DATABASE::Show_Info()
{	json data;
	json data2;
	json data3;
	std::vector <json> data_in;
	std::string data_msg;
	std::cout <<"그래프 데이터\n";
	try
	{	
		std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("SELECT NO,M_NAME, M_RESULT FROM MASK"));
		std::unique_ptr<sql::ResultSet> res(stmnt->executeQuery());
		while(res->next())
		{
			data["NO"] = res->getString(1);
			data["NAME"] = res->getString(2);
			data["RESULT"] = res->getString(3);
			data_in.push_back(data);
		}
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	data2["Result"] = data_in;
	data3["INFO"] = data2;
	data_msg = data3.dump();

	return data_msg;
}

#endif