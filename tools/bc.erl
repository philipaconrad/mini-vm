%% @author Philip Conrad <philipaconrad@gmail.com>
%% @copyright 2013 Philip Conrad
%% @license MIT License
%% @doc A simple bytecode assembler in erlang.

-module(bc).
-export([assemble/1]).


%% @doc Turns a list of numbers into a binary.
-spec assemble(list()) -> binary().
assemble([]) -> <<>>;
assemble(L) -> list_to_binary(L).


%% @private eval function returning an erlang term.
mini_eval(S, Environ) ->
    {ok, Scanned, _} = erl_scan:string(S),
    {ok, Parsed}     = erl_parse:parse_exprs(Scanned),
    {value, Term, _} = erl_eval:exprs(Parsed,Environ),
    Term.


%% @private main function for escript.
main(Args) ->
    try
        [HeadArg|_] = Args,
        T = mini_eval(HeadArg, []),
        io:fwrite(standard_io, "~s", [assemble(T)])
    catch
        _:_ -> usage()
    end;

main(_) -> usage().


usage() ->
    io:format("Usage: escript bc.erl ERL_LIST_TERM~n~n"
              "Description:~n    Takes a list of integers (range 0-255) and prints them to stdout.~n~n"
              "Example:~n    escript bc.erl \"[0,1,2,3, 0,0,1,2, 0,0,0,0].\"~n"),
    halt(1).