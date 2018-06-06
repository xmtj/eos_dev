#include <eosiolib/eosio.hpp>;
#include <eosiolib/print.hpp>;

using namespace std;
class todolist : public eosio::contract
{

  public:
    using eosio::contract::contract;
    //@abi table todos i64
    struct todo
    {
        uint64_t id;
        string description;
        uint64_t completed;

        uint64_t primary_key()const { return id; }
        EOSLIB_SERIALIZE(todo, (id)(description)(completed))
    };

    typedef eosio::multi_index<N(todos), todo> todo_table;
    //@abi action
    void create(account_name author, const uint32_t id, const string &description)
    {
        todo_table todos(_self, author);
        todos.emplace(author, [&](auto &new_todo) {
            new_todo.id = id;
            new_todo.description = description;
            new_todo.completed = 0;
        });
        eosio::print("todo#", id, "create");
    }
    //@abi action
    void complete(account_name author, const uint32_t id)
    {
        todo_table todos(_self, author);
        auto todo_lookup = todos.find(id);
        eosio_assert(todo_lookup != todos.end(), "todo does not exist");
        todos.modify(todo_lookup, author, [&](auto &modifiable_todo) {
            modifiable_todo.completed = 1;
        });
        eosio::print("todo#", id, "marked as completed");
    }
    //@abi action
    void destroy(account_name author, const uint32_t id)
    {
        todo_table todos(_self, author);
        auto todo_lookup = todos.find(id);
        todos.erase(todo_lookup);

        eosio::print("todo#", id, "destroyed");
    }
};
EOSIO_ABI(todolist,(create)(complete)(destroy))