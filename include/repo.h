/*
 * Copyright 2013, Tim Branyen @tbranyen <tim@tabdeveloper.com>
 * @author Michael Robinson @codeofinterest <mike@pagesofinterest.net>
 *
 * Dual licensed under the MIT and GPL licenses.
 */

#ifndef REPO_H
#define REPO_H

#include <v8.h>
#include <node.h>
#include <string>

#include "git2.h"

using namespace node;
using namespace v8;

class GitRepo : public ObjectWrap {
  public:
    static Persistent<Function> constructor_template;
    static void Initialize(Handle<v8::Object> target);

    git_repository* GetValue();
    void SetValue(git_repository* repo);

    void Free();

  protected:
    GitRepo() {}
    ~GitRepo() {}
    static Handle<Value> New(const Arguments& args);

    static Handle<Value> Open(const Arguments& args);
    static void OpenWork(uv_work_t* req);
    static void OpenAfterWork(uv_work_t* req);

    static Handle<Value> Free(const Arguments& args);

    static Handle<Value> Init(const Arguments& args);
    static void InitWork(uv_work_t* req);
    static void InitAfterWork(uv_work_t* req);

  private:
    git_repository* repo;

    struct OpenBaton {
      uv_work_t request;
      const git_error* error;

      git_repository* rawRepo;
      GitRepo *repo;

      std::string path;

      Persistent<Function> callback;
    };

    struct InitBaton {
      uv_work_t request;
      const git_error* error;

      GitRepo* repo;
      git_repository* rawRepo;
      std::string path;
      bool isBare;

      Persistent<Function> callback;
    };
};

#endif
