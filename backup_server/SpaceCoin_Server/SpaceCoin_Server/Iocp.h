#include "session.h"
#include "monster.h"
#include "DB.h"
#include "includePython.h"

#define RANGE 100.f // 실제 거리는 * 1000
#define POSZ 500.f
#define SEE_RANGE 1000.f
#define MONSTER_NORMAL_RANGE 500.f
#define MONSTER_SKILL_RANGE 250.f
#define DATA_LAG 8
#define F_DAMAGE 2.f
#define S_DAMAGE 5.f
#define T_DAMAGE 10.f
#define SKILL_DAMAGE 20.f

class SERVER {
private:
	int							ret;
	int							err_no;
	int							addr_size;

	EXT_OVER					accept_over;

	SOCKET						server;
	SOCKADDR_IN					server_addr;

	SOCKET						client_socket;
	SOCKADDR_IN					client_addr;
public:
	DB							dataBase;
	CoinAPI						coin_api;
	mutex						coin_l;
public:
	SERVER();
	~SERVER();

	int GetNewClientID();

	void error_display(const char* msg, int err_no);
	void disconnect(int client_id);
	void analyze_packet(int client_id, char* p);
	void main_loop();
	void MonsterCreate();
	void initialize();	
};