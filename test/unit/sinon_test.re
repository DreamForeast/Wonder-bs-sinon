open Wonder_Jest;

let _ =
  describe
    "test sinon"
    (
      fun () => {
        open Expect;
        open! Expect.Operators;
        open Sinon;
        let sandbox = getSandboxDefaultVal ();
        beforeAll (fun () => sandbox := createSandbox ());
        afterAll (fun () => restoreSandbox !sandbox);
        test
          "test1"
          (
            fun () => {
              let stub = createEmptyStub !sandbox;
              let func f => f (1, 2);
              func stub;
              getCall stub 0 |> getArgsFromEmptyStub |> expect == [1, 2]
            }
          );
        test
          "test2"
          (
            fun () => {
              let obj = {"func": fun x y => x + y};
              /* let obj  = {
                   pub func x => {
                     x + 1;
                   };
                 }; */
              let stub = createMethodStub !sandbox obj "func";
              let func = obj##func;
              func 1 2;
              getCall stub 0 |> getArgs |> expect == [1, 2]
            }
          );
        describe
          "test extended sinon matcher for jest"
          (
            fun () => {
              test
                "test toCalledWith"
                (
                  fun () => {
                    let obj = {"func": fun x y => x + y};
                    let stub = createMethodStub !sandbox obj "func";
                    let func = obj##func;
                    func 1 2;
                    /* getCall stub 0 |> expect |> toCalledWith [1, 2]; */
                    getCall stub 0 |> expect |> not_ |> toCalledWith [2, 2]
                  }
                );
              test
                "test toCalledBefore"
                (
                  fun () => {
                    let obj = {"func1": fun x y => x + y, "func2": fun x y => x - y};
                    let stub1 = createMethodStub !sandbox obj "func1";
                    let stub2 = createMethodStub !sandbox obj "func2";
                    let func = obj##func1;
                    func 1 2;
                    /* expect stub1 |> not_ |> toCalledBefore stub2; */
                    let func = obj##func2;
                    func 2 3;
                    expect stub1 |> toCalledBefore stub2
                  }
                );
              test
                "test toCalledAfter"
                (
                  fun () => {
                    let obj = {"func1": fun x y => x + y, "func2": fun x y => x - y};
                    let stub1 = createMethodStub !sandbox obj "func1";
                    let stub2 = createMethodStub !sandbox obj "func2";
                    let func = obj##func1;
                    func 1 2;
                    /* expect stub2 |> not_ |> toCalledAfter stub1; */
                    let func = obj##func2;
                    func 2 3;
                    expect stub2 |> toCalledAfter stub1
                  }
                );
              test
                "test toCalled"
                (
                  fun () => {
                    let obj = {"func1": fun x y => x + y};
                    let stub1 = createMethodStub !sandbox obj "func1";
                    let func = obj##func1;
                    /* expect stub1 |> not_ |> toCalled; */
                    func 1 2;
                    expect stub1 |> toCalled
                  }
                );
              test
                "test toCalledOnce"
                (
                  fun () => {
                    let obj = {"func1": fun x y => x + y};
                    let stub1 = createMethodStub !sandbox obj "func1";
                    let func = obj##func1;
                    func 1 2;
                    /* expect stub1 |> toCalledOnce; */
                    func 2 2;
                    expect stub1 |> not_ |> toCalledOnce
                  }
                );
              test
                "test toCalledTwice"
                (
                  fun () => {
                    let obj = {"func1": fun x y => x + y};
                    let stub1 = createMethodStub !sandbox obj "func1";
                    let func = obj##func1;
                    func 1 2;
                    /* expect stub1 |> not_ |> toCalledTwice; */
                    func 2 2;
                    expect stub1 |> toCalledTwice
                  }
                );
              test
                "test toCalledThrice"
                (
                  fun () => {
                    let obj = {"func1": fun x y => x + y};
                    let stub1 = createMethodStub !sandbox obj "func1";
                    let func = obj##func1;
                    func 1 2;
                    /* expect stub1 |> not_ |> toCalledThrice; */
                    func 2 2;
                    /* expect stub1 |> not_ |> toCalledThrice; */
                    func 3 2;
                    expect stub1 |> toCalledThrice
                  }
                );
              test
                "test getCallCount"
                (
                  fun () => {
                    let obj = {"func1": fun x y => x + y, "func2": fun x y => x - y};
                    let stub1 = createMethodStub !sandbox obj "func1";
                    let stub2 = createMethodStub !sandbox obj "func2";
                    let func = obj##func1;
                    func 1 2;
                    func 2 2;
                    let func = obj##func2;
                    func 2 3;
                    /* getCallCount stub1 |> expect == 2; */
                    getCallCount stub2 |> expect == 1
                  }
                )
            }
          )
      }
    );