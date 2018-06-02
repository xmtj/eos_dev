#include <eosiolib/eosio.hpp>;

using namespace eosio;

class vehicle : public eosio::contract
{
  public:
    struct service_rec
    {
        uint64_t pkey;
        account_name customer;
        uint32_t service_date;
        uint32_t odometer;
        auto primary_key() const { return pkey; }
        account_name get_customer() const { return customer; }
        EOSLIB_SERIALIZE(service_rec, (pkey)(customer)(service_date)(odometer));
    };
    typedef multi_index<N(service), service_rec> service_table_type;
    using contract::contract;
    void exec(account_name owner, account_name customer)
    {
        print("hello : ", name{customer});
        service_table_type service_table(current_receiver(), owner);
        uint64_t pkeyf;
        service_table.emplace(owner, [&](auto &s_rec) {
            s_rec.pkey = service_table.available_primary_key();
            pkeyf = s_rec.pkey;
            print(pkeyf);
            s_rec.customer = customer;
            s_rec.service_date = 2000;
            s_rec.odometer = 1000;
        });
        service_rec result = service_table.get(pkeyf);
        print("_", result.pkey);
        print("_", result.customer);
        print("_", result.service_date);
        print("_", result.odometer);
    }
};

EOSIO_ABI(vehicle, (exec))