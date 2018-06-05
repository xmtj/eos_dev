#include <eosiolib/eosio.hpp>;
#include <eosiolib/print.hpp>;
// #include <time.h>;

using namespace std;
class worldtrip : public eosio::contract
{

  public:
    using eosio::contract::contract;
    //@abi table trips i64
    struct trip
    {
        uint64_t id;             // id
        bool is_private = false; // 是否公开
        time trip_time;          // 旅游的时间
        string description;      // 描述
        string pic_url;          // 图片url ，可以放在ipfs上

        uint64_t primary_key() const { return id; }
        EOSLIB_SERIALIZE(trip, (id)(is_private)(trip_time)(description)(pic_url))
    };

    typedef eosio::multi_index<N(trips), trip> trip_table;
    //@abi action
    void create(account_name author, const string &description, const string &pic_url)
    {
        require_auth(author);
        // time_t nowtime;
        // nowtime = time(NULL); //获取当前时间

        //todo 所有的都使用_self指定，然后添加标示账户进行筛选。 
        trip_table trips(_self, author);
        trips.emplace(author, [&](auto &new_trip) {
            new_trip.id = N(author);
            //new_trip.trip_time = nowtime;
            new_trip.description = description;
            new_trip.pic_url = pic_url;
        });
    }
    //@abi action
    void change(account_name author, const bool is_private)
    {
        require_auth(author);
        trip_table trips(_self, author);
        auto trip_lookup = trips.find(N(author));
        eosio_assert(trip_lookup != trips.end(), "todo does not exist");
        trips.modify(trip_lookup, author, [&](auto &modifiable_trip) {
            modifiable_trip.is_private = is_private;
        });
        eosio::print("trips#", N(author), "marked as :", is_private);
    }
    //@abi action
    // vector<trip> gettrips(account_name author)
    // {
    //     trip_table trips(_self, author);
    //     auto trip_lookup = trips.get(id);
    //     trip_lookup.erase(todo_lookup);

    //     eosio::print("trips#", N(author), "destroyed");
    // }
};
EOSIO_ABI(worldtrip, (create)(change))