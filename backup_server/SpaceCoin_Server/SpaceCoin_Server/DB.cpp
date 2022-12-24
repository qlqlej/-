#include "DB.h"

DB::DB()
{

}

DB::~DB()
{
    SQLDisconnect(hdbc);
    SQLFreeHandle(SQL_HANDLE_DBC, hdbc);
    SQLFreeHandle(SQL_HANDLE_ENV, henv);
}

void DB::HandleDiagnosticRecord(SQLHANDLE hHandle, SQLSMALLINT hType, RETCODE RetCode)
{
    SQLSMALLINT iRec = 0;
    SQLINTEGER iError;
    WCHAR wszMessage[1000];
    WCHAR wszState[SQL_SQLSTATE_SIZE + 1];
    if (SQL_INVALID_HANDLE == RetCode) {
        fwprintf(stderr, L"Invalid handle!\n");
        return;
    }
    while (SQLGetDiagRec(hType, hHandle, ++iRec, wszState, &iError, wszMessage,
        (SQLSMALLINT)(sizeof(wszMessage) / sizeof(WCHAR)), (SQLSMALLINT*)NULL) == SQL_SUCCESS) {
        if (wcsncmp(wszState, L"01004", 5)) {
            fwprintf(stderr, L"[%5.5s] %s (%d)\n", wszState, wszMessage, iError);
        }
    }
}

void DB::Initialize()
{
    retcode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);
    if (SQL_SUCCESS == retcode || SQL_SUCCESS_WITH_INFO == retcode) {
        retcode = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);
        if (SQL_SUCCESS == retcode || SQL_SUCCESS_WITH_INFO == retcode) {
            retcode = SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc);
            if (SQL_SUCCESS == retcode || SQL_SUCCESS_WITH_INFO == retcode) {
                SQLSetConnectAttr(hdbc, SQL_LOGIN_TIMEOUT, (SQLPOINTER)5, 0);
                retcode = SQLConnect(hdbc, (SQLWCHAR*)L"SpaceCoin", SQL_NTS, (SQLWCHAR*)NULL, 0, NULL, 0);
                if (SQL_SUCCESS == retcode || SQL_SUCCESS_WITH_INFO == retcode) {
                    cout << "SQL Server Connected!\n";
                    retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
                }
                else {
                    cout << "SQL Server connection failed\n";
                    SQLDisconnect(hdbc);
                }                
            }
            else SQLFreeHandle(SQL_HANDLE_DBC, hdbc);
        }        
    }
    else SQLFreeHandle(SQL_HANDLE_ENV, henv);
}

bool DB::ExistAccount(const char* id)
{
    bool ret = false;
    string sql = "SELECT * FROM [SpaceCoin].[dbo].[USER_ID] WHERE ID = '";
    sql += id + (string)"'";
    wstring wsql = wstring(sql.begin(), sql.end());
    const wchar_t* wtsql = wsql.c_str();
    retcode = SQLExecDirect(hstmt, (SQLWCHAR*)wtsql, SQL_NTS);
    if (SQL_SUCCESS == retcode || SQL_SUCCESS_WITH_INFO == retcode) {        
        for (int i = 0; ; i++) {
            retcode = SQLFetch(hstmt);
            if (SQL_ERROR == retcode) {
                HandleDiagnosticRecord(hstmt, SQL_HANDLE_STMT, retcode);
            }
            if (SQL_SUCCESS == retcode || SQL_SUCCESS_WITH_INFO == retcode) {
                ret = true;
            }
            else
                break;
        }
    }
    retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
    return ret;
}

bool DB::SearchAccount(const char* id, const char* pw, SC_LOGIN_INFO_PACKET& p)
{
    bool ret = false;
    string sql = "SELECT * FROM [SpaceCoin].[dbo].[USER_ID] WHERE ID = '";
    sql += id + (string)"' and PW = '" + pw + "'";
    wstring wsql = wstring(sql.begin(), sql.end());
    const wchar_t* wtsql = wsql.c_str();
    retcode = SQLExecDirect(hstmt, (SQLWCHAR*)wtsql, SQL_NTS); // 로그인시 입력한 ID 와 PW로 USER_ID 테이블에 존재하는지 검색
    if (SQL_SUCCESS == retcode || SQL_SUCCESS_WITH_INFO == retcode) {        
        SQLWCHAR p_id[MAX_ID_LEN]{}, p_pw[MAX_PW_LEN]{}, p_name[MAX_NAME_LEN]{};
        SQLLEN cbP_id = 0, cbP_pw = 0, cbP_name = 0;
        retcode = SQLBindCol(hstmt, 1, SQL_C_WCHAR, p_id, MAX_ID_LEN, &cbP_id);
        retcode = SQLBindCol(hstmt, 2, SQL_C_WCHAR, p_pw, MAX_PW_LEN, &cbP_pw);
        retcode = SQLBindCol(hstmt, 3, SQL_C_WCHAR, p_name, MAX_NAME_LEN, &cbP_name);
        for (int i = 0; ; i++) {
            retcode = SQLFetch(hstmt);
            if (SQL_ERROR == retcode) {
                HandleDiagnosticRecord(hstmt, SQL_HANDLE_STMT, retcode);
            }
            if (SQL_SUCCESS == retcode || SQL_SUCCESS_WITH_INFO == retcode) {
                size_t tcnt;
                wcstombs_s(&tcnt, p.name, sizeof(p.name), p_name, 20);
                p.name[tcnt] = 0;
                ret = true;
            }
            else
                break;
        }        
    }
    retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
    if (false == ret)
        return ret;

    ret = false;
    sql = "SELECT * FROM [SpaceCoin].[dbo].[USER_DATA] WHERE ID = '";
    sql += id + (string)"'";
    wsql = wstring(sql.begin(), sql.end());
    wtsql = wsql.c_str();
    retcode = SQLExecDirect(hstmt, (SQLWCHAR*)wtsql, SQL_NTS); // USER_DATA 테이블에서 해당 ID의 정보 불러오기
    if (SQL_SUCCESS == retcode || SQL_SUCCESS_WITH_INFO == retcode) {
        SQLWCHAR p_id[MAX_ID_LEN]{};
        float p_hp = 0;
        long p_a_coin = 0, p_b_coin = 0, p_c_coin = 0, p_gold = 0;
        float p_x = 0, p_y = 0, p_z = 0, p_pitch = 0, p_yaw = 0, p_roll = 0;
        int p_character_type = 0, p_map_type = 0;
        SQLLEN cbP_id = 0, cbP_x = 0, cbP_y = 0, cbP_z = 0, cbP_pitch = 0, cbP_yaw = 0, cbP_roll = 0;
        SQLLEN cbP_character_type = 0, cbP_map_type = 0;
        SQLLEN cbP_hp = 0, cbP_a_coin = 0, cbP_b_coin = 0, cbP_c_coin = 0, cbP_gold = 0;
        retcode = SQLBindCol(hstmt, 1, SQL_C_WCHAR, p_id, MAX_ID_LEN, &cbP_id);
        retcode = SQLBindCol(hstmt, 2, SQL_C_FLOAT, &p_hp, sizeof(float), &cbP_hp);
        retcode = SQLBindCol(hstmt, 3, SQL_C_LONG, &p_a_coin, sizeof(int), &cbP_a_coin);
        retcode = SQLBindCol(hstmt, 4, SQL_C_LONG, &p_b_coin, sizeof(int), &cbP_b_coin);
        retcode = SQLBindCol(hstmt, 5, SQL_C_LONG, &p_c_coin, sizeof(int), &cbP_c_coin);
        retcode = SQLBindCol(hstmt, 6, SQL_C_LONG, &p_gold, sizeof(int), &cbP_gold);
        retcode = SQLBindCol(hstmt, 7, SQL_C_FLOAT, &p_x, sizeof(float), &cbP_x);
        retcode = SQLBindCol(hstmt, 8, SQL_C_FLOAT, &p_y, sizeof(float), &cbP_y);
        retcode = SQLBindCol(hstmt, 9, SQL_C_FLOAT, &p_z, sizeof(float), &cbP_z);
        retcode = SQLBindCol(hstmt, 10, SQL_C_FLOAT, &p_pitch, sizeof(float), &cbP_pitch);
        retcode = SQLBindCol(hstmt, 11, SQL_C_FLOAT, &p_yaw, sizeof(float), &cbP_yaw);
        retcode = SQLBindCol(hstmt, 12, SQL_C_FLOAT, &p_roll, sizeof(float), &cbP_roll);
        retcode = SQLBindCol(hstmt, 13, SQL_C_TINYINT, &p_character_type, sizeof(int), &cbP_character_type);
        retcode = SQLBindCol(hstmt, 14, SQL_C_TINYINT, &p_map_type, sizeof(int), &cbP_map_type);
        for (int i = 0; ; i++) {
            retcode = SQLFetch(hstmt);
            if (SQL_ERROR == retcode) {
                HandleDiagnosticRecord(hstmt, SQL_HANDLE_STMT, retcode);
            }
            if (SQL_SUCCESS == retcode || SQL_SUCCESS_WITH_INFO == retcode) {
                p.hp = p_hp;
                p.a_coin = p_a_coin;
                p.b_coin = p_b_coin;
                p.c_coin = p_c_coin;
                p.gold = p_gold;
                switch (p_character_type)
                {
                case 0:
                    p.character_type = CHARACTER_TYPE::HUMAN;
                    break;
                case 1:
                    p.character_type = CHARACTER_TYPE::SPACESHIP;
                    break;
                }
                switch (p_map_type)
                {
                case 0:
                    p.map_type = MAP_TYPE::SPACE;
                    break;
                case 1:
                    p.map_type = MAP_TYPE::ICE;
                    break;
                case 2:
                    p.map_type = MAP_TYPE::SAND;
                    break;
                case 3:
                    p.map_type = MAP_TYPE::WATER;
                    break;
                }
                p.x = p_x;
                p.y = p_y;
                p.z = p_z;
                p.pitch = p_pitch;
                p.yaw = p_yaw;
                p.roll = p_roll;
                ret = true;
            }
            else
                break;
        }
    }
    retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
    if (false == ret)
        return ret;

    ret = false;
    sql = "SELECT * FROM [SpaceCoin].[dbo].[USER_ITEM] WHERE ID = '";
    sql += id + (string)"'";
    wsql = wstring(sql.begin(), sql.end());
    wtsql = wsql.c_str();
    retcode = SQLExecDirect(hstmt, (SQLWCHAR*)wtsql, SQL_NTS); // USER_ITEM 테이블에서 해당 ID의 ITEM 정보 불러오기
    if (SQL_SUCCESS == retcode || SQL_SUCCESS_WITH_INFO == retcode) {
        SQLWCHAR p_id[MAX_ID_LEN]{};
        int p_critical_up = 0, p_speed_up = 0, p_attack_up = 0, p_hp_up = 0, p_recover_hp_up = 0;
        int p_sniper_up = 0, p_attack_hp_up = 0, p_launcher_up = 0, p_launcher_range_up = 0, p_jump_up = 0;
        SQLLEN cbP_id = 0, cbP_critical_up = 0, cbP_speed_up = 0, cbP_attack_up = 0, cbP_hp_up = 0, cbP_recover_hp_up = 0;
        SQLLEN cbP_sniper_up = 0, cbP_attack_hp_up = 0, cbP_launcher_up = 0, cbP_launcher_range_up = 0, cbP_jump_up = 0;
        retcode = SQLBindCol(hstmt, 1, SQL_C_WCHAR, p_id, MAX_ID_LEN, &cbP_id);
        retcode = SQLBindCol(hstmt, 2, SQL_C_TINYINT, &p_critical_up, sizeof(int), &cbP_critical_up);
        retcode = SQLBindCol(hstmt, 3, SQL_C_TINYINT, &p_speed_up, sizeof(int), &cbP_speed_up);
        retcode = SQLBindCol(hstmt, 4, SQL_C_TINYINT, &p_attack_up, sizeof(int), &cbP_attack_up);
        retcode = SQLBindCol(hstmt, 5, SQL_C_TINYINT, &p_hp_up, sizeof(int), &cbP_hp_up);
        retcode = SQLBindCol(hstmt, 6, SQL_C_TINYINT, &p_recover_hp_up, sizeof(int), &cbP_recover_hp_up);
        retcode = SQLBindCol(hstmt, 7, SQL_C_TINYINT, &p_sniper_up, sizeof(int), &cbP_sniper_up);
        retcode = SQLBindCol(hstmt, 8, SQL_C_TINYINT, &p_attack_hp_up, sizeof(int), &cbP_attack_hp_up);
        retcode = SQLBindCol(hstmt, 9, SQL_C_TINYINT, &p_launcher_up, sizeof(int), &cbP_launcher_up);
        retcode = SQLBindCol(hstmt, 10, SQL_C_TINYINT, &p_launcher_range_up, sizeof(int), &cbP_launcher_range_up);
        retcode = SQLBindCol(hstmt, 11, SQL_C_TINYINT, &p_jump_up, sizeof(int), &cbP_jump_up);
        for (int i = 0; ; i++) {
            retcode = SQLFetch(hstmt);
            if (SQL_ERROR == retcode) {
                HandleDiagnosticRecord(hstmt, SQL_HANDLE_STMT, retcode);
            }
            if (SQL_SUCCESS == retcode || SQL_SUCCESS_WITH_INFO == retcode) {
                p.critical_up = p_critical_up;
                p.speed_up = p_speed_up;
                p.attack_up = p_attack_up;
                p.hp_up = p_hp_up;
                p.recover_hp_up = p_recover_hp_up;
                p.sniper_up = p_sniper_up;
                p.attack_hp_up = p_attack_hp_up;
                p.launcher_up = p_launcher_up;
                p.launcher_range_up = p_launcher_range_up;
                p.jump_up = p_jump_up;
                ret = true;
            }
            else
                break;
        }
    }
    retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);

    return ret;
}

bool DB::SignupAccount(const char* nickname, const char* id, const char* pw)
{
    if (true == ExistAccount(id)) // 가입할 ID가 존재하는 지 검색
        return false;

    bool ret = false;  
    string sql = "INSERT INTO [SpaceCoin].[dbo].[USER_ID] (ID, PW, NICKNAME) VALUES ('";
    sql += id + (string)"', '" + pw + (string)"', '" + nickname + (string)"')";
    wstring wsql = wstring(sql.begin(), sql.end());
    const wchar_t* wtsql = wsql.c_str();
    retcode = SQLExecDirect(hstmt, (SQLWCHAR*)wtsql, SQL_NTS); // USER_ID 테이블에 데이터 삽입
    if (SQL_SUCCESS == retcode || SQL_SUCCESS_WITH_INFO == retcode) {       
        ret = true;
    }
    retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);

    sql = "INSERT INTO [SpaceCoin].[dbo].[USER_DATA] (ID, HP, A_COIN, B_COIN, C_COIN, GOLD, X, Y, Z, PITCH, YAW, ROLL, CHARACTER_TYPE, MAP_TYPE) VALUES ('";
    sql += id + (string)"', " + (string)"100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0)";
    wsql = wstring(sql.begin(), sql.end());
    wtsql = wsql.c_str();
    retcode = SQLExecDirect(hstmt, (SQLWCHAR*)wtsql, SQL_NTS); // USER_DATA 테이블에 데이터 삽입
    if (SQL_SUCCESS == retcode || SQL_SUCCESS_WITH_INFO == retcode) {
        ret = true;
    }
    retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);

    sql = "INSERT INTO [SpaceCoin].[dbo].[USER_ITEM] (ID, CRITICAL_UP, SPEED_UP, ATTACK_UP, HP_UP, RECOVER_HP_UP, SNIPER_UP, ATTACK_HP_UP, LAUNCHER_UP, LAUNCHER_RANGE_UP, JUMP_UP) VALUES ('";
    sql += id + (string)"', " + (string)"0, 0, 0, 0, 0, 0, 0, 0, 0, 0)";
    wsql = wstring(sql.begin(), sql.end());
    wtsql = wsql.c_str();
    retcode = SQLExecDirect(hstmt, (SQLWCHAR*)wtsql, SQL_NTS); // USER_ITEM 테이블에 데이터 삽입
    if (SQL_SUCCESS == retcode || SQL_SUCCESS_WITH_INFO == retcode) {
        ret = true;
    }
    retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);

    return ret;
}

bool DB::SavePlayerInfo(const char* id, float hp, int a_coin, int b_coin, int c_coin, int gold, float x, float y, float z,
    float pitch, float yaw, float roll, int character_type, int map_type, int critical_up, int speed_up, int attack_up, int hp_up, int recover_hp_up,
    int sniper_up, int attack_hp_up, int launcher_up, int launcher_range_up, int jump_up)
{
    bool ret = false;
    string sql = "UPDATE [SpaceCoin].[dbo].[USER_DATA] SET HP = ";
    sql += to_string(hp) + (string)", A_COIN = " + to_string(a_coin) + (string)", B_COIN = " + to_string(b_coin)
        + (string)", C_COIN = " + to_string(c_coin) + (string)", GOLD = " + to_string(gold) + (string)", X = " + to_string(x)
        + (string)", Y = " + to_string(y) + (string)", Z = " + to_string(z) + (string)", PITCH = " + to_string(pitch)
        + (string)", YAW = " + to_string(yaw) + (string)", ROLL = " + to_string(roll) + (string)", CHARACTER_TYPE = " + to_string(character_type)
        + (string)", MAP_TYPE = " + to_string(map_type) + (string)" WHERE ID = '" + id + (string)"'";
    wstring wsql = wstring(sql.begin(), sql.end());
    const wchar_t* wtsql = wsql.c_str();
    retcode = SQLExecDirect(hstmt, (SQLWCHAR*)wtsql, SQL_NTS); // USER_DATA 저장
    if (SQL_SUCCESS == retcode || SQL_SUCCESS_WITH_INFO == retcode) {
        ret = true;
    }
    retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);

    sql = "UPDATE [SpaceCoin].[dbo].[USER_ITEM] SET CRITICAL_UP = ";
    sql += to_string(critical_up) + (string)", SPEED_UP = " + to_string(speed_up) + (string)", ATTACK_UP = " + to_string(attack_up)
        + (string)", HP_UP = " + to_string(hp_up) + (string)", RECOVER_HP_UP = " + to_string(recover_hp_up) + (string)", SNIPER_UP = " + to_string(sniper_up)
        + (string)", ATTACK_HP_UP = " + to_string(attack_hp_up) + (string)", LAUNCHER_UP = " + to_string(launcher_up) + (string)", LAUNCHER_RANGE_UP = " + to_string(launcher_range_up)
        + (string)", JUMP_UP = " + to_string(jump_up) + (string)" WHERE ID = '" + id + (string)"'";
    wsql = wstring(sql.begin(), sql.end());
    wtsql = wsql.c_str();
    retcode = SQLExecDirect(hstmt, (SQLWCHAR*)wtsql, SQL_NTS); // USER_ITEM 저장
    if (SQL_SUCCESS == retcode || SQL_SUCCESS_WITH_INFO == retcode) {
        ret = true;
    }
    retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);

    return ret;
}
