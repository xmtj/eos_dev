#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>

// 视频网站：http://kongyixueyuan.com
// 个人博客：http://liyuechun.org
// 公众号：区块链部落
// 进技术群，请加微信（kongyixueyuan）

//用eosio命名空间
using namespace eosio;

//所有的智能合约都继承自contract类
class Hello : public eosio::contract {

  public:
      using contract::contract;

      /// @abi action
      void hi( account_name user ) {
         print( "Hello, ", name{user} );
      }

};
EOSIO_ABI( Hello, (hi) )
