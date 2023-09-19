//
//  main.m
//  QYChromiumTest
//
//  Created by yinquan on 2023/8/16.
//

#import <Cocoa/Cocoa.h>
#import <QYView/QYEntry.h>
//int main(int argc, const char * argv[]) {
//    @autoreleasepool {
//        // Setup code that might create autoreleased objects goes here.
//    }
//    NSBundle *viewBundle = [NSBundle bundleWithIdentifier:@"qy.QYView"];
//    //TODO:临时解决，复制snapshot到Framework主目录
//    //V8_USE_EXTERNAL_STARTUP_DATA不知道为啥没有编译进去
//    initJS(viewBundle.resourcePath.UTF8String);
//    return NSApplicationMain(argc, argv);
//}

enum TOKEN_TYPE {
    tok_other = -1,//其他
    tok_identifier = 1,//文本
    tok_number = 2,//数字
};

#include <string>


class QYExpression {
    
};

class QYNumberExpression : public QYExpression {
    
};

class QYStringExpression : public QYExpression {
public:
    QYStringExpression(std::string str): mStr(str) {}
    std::string mStr;
};

class QYVariableExpression : public QYExpression {
    
};

class QYCallExpression : public QYExpression{
public:
    QYExpression *mCallee;
};

class QYFunctionCallExpression : public QYCallExpression {
public:
    std::string mFunc;
    std::vector<QYExpression> mArgs;
};

class QYPropertyCallExpression : public QYCallExpression {
public:
    QYPropertyCallExpression(QYExpression *callee, std::string property) : mCallee(callee), mProperty(property){};
    std::string mProperty;
};

class QYArrayCallExpression : public QYCallExpression {
public:
    QYArrayCallExpression(QYExpression *callee, int index): mCallee(callee), mIndex(index){};
    int mIndex;
};


struct QYToken {
    TOKEN_TYPE type;
    std::string identifier;
    double number;
};


//
class QYTokenParser {
public:
    std::string src;
    int curIndex = 0;
    int lastChar = ' ';
    QYToken currentToken;
    
    int getChar() {
        return src[curIndex++];
    }
    
    int currentChar() {
        return src[curIndex];
    }
    
    QYToken getNextToken() {
        while(isspace(lastChar)) {
            lastChar = getChar();
        }
        //字母开头
        if (isalpha(lastChar)) {
            std::string identifier = std::to_string(lastChar);
            while(isalnum(lastChar = getChar())) {
                identifier += lastChar;
            }
            currentToken = {tok_identifier, identifier, 0};
            return currentToken;
            
        }
        //数字开头
        if (isdigit(lastChar)) {
            std::string numberStr = std::to_string(lastChar);
            while(isnumber(lastChar = getChar()) || lastChar == '.') {
                numberStr += lastChar;
            }
            currentToken = {tok_number, nullptr, strtod(numberStr.c_str(), nullptr)};
            return currentToken;
        }
        currentToken = {tok_other, nullptr, 0};
        return currentToken;
    };
    
    void parseExp() {
        
    }
    //  ()的情况，当currentChar确定是(时调用
    void parseParentExp() {
        //略过(
        getNextToken();
        //处理完()内的表达式
        parseExp();//TODO:返回个值
        if (currentChar() != ')') {
            throw "()表达式内错误";
        }
        //略过)
        getNextToken();
        //TODO:返回个值
    }

//    a.b()[3]().c
    //变量或者方法调用
    QYExpression *parseIdentifierExp(QYExpression *callee) {
        std::string identifier = currentToken.identifier;
        getNextToken();
        return _parseIdentifierExp(new QYStringExpression(identifier));
    }
    
    QYExpression *_parseIdentifierExp(QYExpression *callee) {
        QYExpression *expression = nullptr;
        //确定是方法调用了
        if (currentChar() == '(') {
            //TODO:返回个值
            expression = parseFunctionCallExp(callee);
        }
        //确定是属性访问
        else if (currentChar() == '.') {
            //TODO:返回个值
            expression = parsePropertyCallExp(callee);
        }
        //确定是数组访问
        else if (currentChar() == '[') {
            //TODO:返回个值
            expression = parseArrayAccessExp(callee);
        }
        //都不是，那就暂定变量了，后面有其他情况再加
        else {
            //TODO:返回个值
        }

        int curChar = currentChar();
        if (curChar == '.' || curChar == '[' || curChar == '(' ) {
            parseIdentifierExp(expression);
        }

    }

    
    
    void parseNumberExp() {
        //确定当前是数字了
        currentToken.number;
        
        getNextToken();
        //TODO:返回个值
    }
    
    QYFunctionCallExpression* parseFunctionCallExp(QYExpression *callee) {
        //当前是(
        getNextToken();
        //如果有参数
        if(currentChar() != ')') {
            std::vector<QYExpression> args;
            while(true) {
                QYExpression *arg = parseExp();
                if (!arg) {
                    throw "方法参数解析错误";
                }
                args.push_back(arg);
                //调用结束
                if (currentChar() == ')') {
                    break;
                }
                //还有参数，这里应该是, 不然就报错
                else if (currentChar() != ',') {
                    throw "方法调用参数错误";
                }
                //继续读取参数
                getNextToken();
            }
        }
        QYFunctionCallExpression *funcExp = new QYFunctionCallExpression()
        //略过)
        getNextToken();
    }
    
    QYPropertyCallExpression* parsePropertyCallExp(QYExpression *callee) {
        //当前是.，获取下一个token
        getNextToken();
        if (currentToken.type != tok_identifier) {
            throw ".调用错误，不是标识符";
        }
        QYPropertyCallExpression *propertyExp = new QYPropertyCallExpression(callee, currentToken.identifier);
        getNextToken();
        return propertyExp;
    }
    
    QYArrayCallExpression* parseArrayAccessExp(QYExpression *callee) {
        //当前是[
        getNextToken();
        if (currentToken.type != tok_number) {
            throw "[] 调用错误，不是数字";
        }
        //略过数字
        getNextToken();
        //略过]
        getNextToken();
    }
    
    void parseStringExp() {
        
    }

    
    void parseVariableExp() {
        
    }
};





int main(int argc, const char * argv[]) {
    
    return 0;
}



#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

//===----------------------------------------------------------------------===//
// Lexer
//===----------------------------------------------------------------------===//

// The lexer returns tokens [0-255] if it is an unknown character, otherwise one
// of these for known things.
enum Token {
  tok_eof = -1,

  // commands
  tok_def = -2,
  tok_extern = -3,

  // primary
  tok_identifier = -4,
  tok_number = -5
};

static std::string IdentifierStr; // Filled in if tok_identifier
static double NumVal;             // Filled in if tok_number

/// gettok - Return the next token from standard input.
static int gettok() {
  static int LastChar = ' ';

  // Skip any whitespace.
  while (isspace(LastChar))
    LastChar = getchar();

  if (isalpha(LastChar)) { // identifier: [a-zA-Z][a-zA-Z0-9]*
    IdentifierStr = LastChar;
    while (isalnum((LastChar = getchar())))
      IdentifierStr += LastChar;

    if (IdentifierStr == "def")
      return tok_def;
    if (IdentifierStr == "extern")
      return tok_extern;
    return tok_identifier;
  }

  if (isdigit(LastChar) || LastChar == '.') { // Number: [0-9.]+
    std::string NumStr;
    do {
      NumStr += LastChar;
      LastChar = getchar();
    } while (isdigit(LastChar) || LastChar == '.');

    NumVal = strtod(NumStr.c_str(), nullptr);
    return tok_number;
  }

  if (LastChar == '#') {
    // Comment until end of line.
    do
      LastChar = getchar();
    while (LastChar != EOF && LastChar != '\n' && LastChar != '\r');

    if (LastChar != EOF)
      return gettok();
  }

  // Check for end of file.  Don't eat the EOF.
  if (LastChar == EOF)
    return tok_eof;

  // Otherwise, just return the character as its ascii value.
  int ThisChar = LastChar;
  LastChar = getchar();
  return ThisChar;
}

//===----------------------------------------------------------------------===//
// Abstract Syntax Tree (aka Parse Tree)
//===----------------------------------------------------------------------===//

namespace {

/// ExprAST - Base class for all expression nodes.
class ExprAST {
public:
  virtual ~ExprAST() = default;
};

/// NumberExprAST - Expression class for numeric literals like "1.0".
class NumberExprAST : public ExprAST {
  double Val;

public:
  NumberExprAST(double Val) : Val(Val) {}
};

/// VariableExprAST - Expression class for referencing a variable, like "a".
class VariableExprAST : public ExprAST {
  std::string Name;

public:
  VariableExprAST(const std::string &Name) : Name(Name) {}
};

/// BinaryExprAST - Expression class for a binary operator.
class BinaryExprAST : public ExprAST {
  char Op;
  std::unique_ptr<ExprAST> LHS, RHS;

public:
  BinaryExprAST(char Op, std::unique_ptr<ExprAST> LHS,
                std::unique_ptr<ExprAST> RHS)
      : Op(Op), LHS(std::move(LHS)), RHS(std::move(RHS)) {}
};

/// CallExprAST - Expression class for function calls.
class CallExprAST : public ExprAST {
  std::string Callee;
  std::vector<std::unique_ptr<ExprAST>> Args;

public:
  CallExprAST(const std::string &Callee,
              std::vector<std::unique_ptr<ExprAST>> Args)
      : Callee(Callee), Args(std::move(Args)) {}
};

/// PrototypeAST - This class represents the "prototype" for a function,
/// which captures its name, and its argument names (thus implicitly the number
/// of arguments the function takes).
class PrototypeAST {
  std::string Name;
  std::vector<std::string> Args;

public:
  PrototypeAST(const std::string &Name, std::vector<std::string> Args)
      : Name(Name), Args(std::move(Args)) {}

  const std::string &getName() const { return Name; }
};

/// FunctionAST - This class represents a function definition itself.
class FunctionAST {
  std::unique_ptr<PrototypeAST> Proto;
  std::unique_ptr<ExprAST> Body;

public:
  FunctionAST(std::unique_ptr<PrototypeAST> Proto,
              std::unique_ptr<ExprAST> Body)
      : Proto(std::move(Proto)), Body(std::move(Body)) {}
};

} // end anonymous namespace

//===----------------------------------------------------------------------===//
// Parser
//===----------------------------------------------------------------------===//

/// CurTok/getNextToken - Provide a simple token buffer.  CurTok is the current
/// token the parser is looking at.  getNextToken reads another token from the
/// lexer and updates CurTok with its results.
static int CurTok;
static int getNextToken() { return CurTok = gettok(); }

/// BinopPrecedence - This holds the precedence for each binary operator that is
/// defined.
static std::map<char, int> BinopPrecedence;

/// GetTokPrecedence - Get the precedence of the pending binary operator token.
static int GetTokPrecedence() {
  if (!isascii(CurTok))
    return -1;

  // Make sure it's a declared binop.
  int TokPrec = BinopPrecedence[CurTok];
  if (TokPrec <= 0)
    return -1;
  return TokPrec;
}

/// LogError* - These are little helper functions for error handling.
std::unique_ptr<ExprAST> LogError(const char *Str) {
  fprintf(stderr, "Error: %s\n", Str);
  return nullptr;
}
std::unique_ptr<PrototypeAST> LogErrorP(const char *Str) {
  LogError(Str);
  return nullptr;
}

static std::unique_ptr<ExprAST> ParseExpression();

/// numberexpr ::= number
static std::unique_ptr<ExprAST> ParseNumberExpr() {
  auto Result = std::make_unique<NumberExprAST>(NumVal);
  getNextToken(); // consume the number
  return std::move(Result);
}

/// parenexpr ::= '(' expression ')'
static std::unique_ptr<ExprAST> ParseParenExpr() {
  getNextToken(); // eat (.
  auto V = ParseExpression();
  if (!V)
    return nullptr;

  if (CurTok != ')')
    return LogError("expected ')'");
  getNextToken(); // eat ).
  return V;
}

/// identifierexpr
///   ::= identifier
///   ::= identifier '(' expression* ')'
static std::unique_ptr<ExprAST> ParseIdentifierExpr() {
  std::string IdName = IdentifierStr;

  getNextToken(); // eat identifier.

  if (CurTok != '(') // Simple variable ref.
    return std::make_unique<VariableExprAST>(IdName);

  // Call.
  getNextToken(); // eat (
  std::vector<std::unique_ptr<ExprAST>> Args;
  if (CurTok != ')') {
    while (true) {
      if (auto Arg = ParseExpression())
        Args.push_back(std::move(Arg));
      else
        return nullptr;

      if (CurTok == ')')
        break;

      if (CurTok != ',')
        return LogError("Expected ')' or ',' in argument list");
      getNextToken();
    }
  }

  // Eat the ')'.
  getNextToken();

  return std::make_unique<CallExprAST>(IdName, std::move(Args));
}

/// primary
///   ::= identifierexpr
///   ::= numberexpr
///   ::= parenexpr
static std::unique_ptr<ExprAST> ParsePrimary() {
  switch (CurTok) {
  default:
    return LogError("unknown token when expecting an expression");
  case tok_identifier:
    return ParseIdentifierExpr();
  case tok_number:
    return ParseNumberExpr();
  case '(':
    return ParseParenExpr();
  }
}

/// binoprhs
///   ::= ('+' primary)*
static std::unique_ptr<ExprAST> ParseBinOpRHS(int ExprPrec,
                                              std::unique_ptr<ExprAST> LHS) {
  // If this is a binop, find its precedence.
  while (true) {
    int TokPrec = GetTokPrecedence();

    // If this is a binop that binds at least as tightly as the current binop,
    // consume it, otherwise we are done.
    if (TokPrec < ExprPrec)
      return LHS;

    // Okay, we know this is a binop.
    int BinOp = CurTok;
    getNextToken(); // eat binop

    // Parse the primary expression after the binary operator.
    auto RHS = ParsePrimary();
    if (!RHS)
      return nullptr;

    // If BinOp binds less tightly with RHS than the operator after RHS, let
    // the pending operator take RHS as its LHS.
    int NextPrec = GetTokPrecedence();
    if (TokPrec < NextPrec) {
      RHS = ParseBinOpRHS(TokPrec + 1, std::move(RHS));
      if (!RHS)
        return nullptr;
    }

    // Merge LHS/RHS.
    LHS =
        std::make_unique<BinaryExprAST>(BinOp, std::move(LHS), std::move(RHS));
  }
}

/// expression
///   ::= primary binoprhs
///
static std::unique_ptr<ExprAST> ParseExpression() {
  auto LHS = ParsePrimary();
  if (!LHS)
    return nullptr;

  return ParseBinOpRHS(0, std::move(LHS));
}

/// prototype
///   ::= id '(' id* ')'
static std::unique_ptr<PrototypeAST> ParsePrototype() {
  if (CurTok != tok_identifier)
    return LogErrorP("Expected function name in prototype");

  std::string FnName = IdentifierStr;
  getNextToken();

  if (CurTok != '(')
    return LogErrorP("Expected '(' in prototype");

  std::vector<std::string> ArgNames;
  while (getNextToken() == tok_identifier)
    ArgNames.push_back(IdentifierStr);
  if (CurTok != ')')
    return LogErrorP("Expected ')' in prototype");

  // success.
  getNextToken(); // eat ')'.

  return std::make_unique<PrototypeAST>(FnName, std::move(ArgNames));
}

/// definition ::= 'def' prototype expression
static std::unique_ptr<FunctionAST> ParseDefinition() {
  getNextToken(); // eat def.
  auto Proto = ParsePrototype();
  if (!Proto)
    return nullptr;

  if (auto E = ParseExpression())
    return std::make_unique<FunctionAST>(std::move(Proto), std::move(E));
  return nullptr;
}

/// toplevelexpr ::= expression
static std::unique_ptr<FunctionAST> ParseTopLevelExpr() {
  if (auto E = ParseExpression()) {
    // Make an anonymous proto.
    auto Proto = std::make_unique<PrototypeAST>("__anon_expr",
                                                std::vector<std::string>());
    return std::make_unique<FunctionAST>(std::move(Proto), std::move(E));
  }
  return nullptr;
}

/// external ::= 'extern' prototype
static std::unique_ptr<PrototypeAST> ParseExtern() {
  getNextToken(); // eat extern.
  return ParsePrototype();
}

//===----------------------------------------------------------------------===//
// Top-Level parsing
//===----------------------------------------------------------------------===//

static void HandleDefinition() {
  if (ParseDefinition()) {
    fprintf(stderr, "Parsed a function definition.\n");
  } else {
    // Skip token for error recovery.
    getNextToken();
  }
}

static void HandleExtern() {
  if (ParseExtern()) {
    fprintf(stderr, "Parsed an extern\n");
  } else {
    // Skip token for error recovery.
    getNextToken();
  }
}

static void HandleTopLevelExpression() {
  // Evaluate a top-level expression into an anonymous function.
  if (ParseTopLevelExpr()) {
    fprintf(stderr, "Parsed a top-level expr\n");
  } else {
    // Skip token for error recovery.
    getNextToken();
  }
}

/// top ::= definition | external | expression | ';'
static void MainLoop() {
  while (true) {
    fprintf(stderr, "ready> ");
    switch (CurTok) {
    case tok_eof:
      return;
    case ';': // ignore top-level semicolons.
      getNextToken();
      break;
    case tok_def:
      HandleDefinition();
      break;
    case tok_extern:
      HandleExtern();
      break;
    default:
      HandleTopLevelExpression();
      break;
    }
  }
}

//===----------------------------------------------------------------------===//
// Main driver code.
//===----------------------------------------------------------------------===//

int main() {
  // Install standard binary operators.
  // 1 is lowest precedence.
  BinopPrecedence['<'] = 10;
  BinopPrecedence['+'] = 20;
  BinopPrecedence['-'] = 20;
  BinopPrecedence['*'] = 40; // highest.

  // Prime the first token.
  fprintf(stderr, "ready> ");
  getNextToken();

  // Run the main "interpreter loop" now.
  MainLoop();

  return 0;
}
