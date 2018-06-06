#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>

//用eosio命名空间
using namespace eosio;

//所有的智能合约都继承自contract类
class Hello : public eosio::contract
{

public:
  using contract::contract;

  /// @abi action
  void hi(account_name user)
  {
    print("Hello, ", name{user});

    // 向dice转账，由于使用的是eos token，转账通过eosio.token合约执行
    // action(
    //     permission_level{from, N(active)},
    //     N(eosio.token), N(transfer),
    //     std::make_tuple(from, _self, quantity, std::string("")))
    //     .send();
  }
};
EOSIO_ABI(Hello, (hi))
