#pragma once

#include "ds/Array.hpp"
#include "ds/String.hpp"
#include "stone/Token.hpp"
#include "stone/Data.hpp"
#include "Data.hpp"

namespace stone {
    typedef char char_type;

    class ASTVisitor;

    class ExprAST;

    class AST {
    public:
        AST() : m_pos(-1, -1) {
        }

        virtual void accept(ASTVisitor *visitor);

        virtual ~AST() {
        }

        CodePosition pos() const {
            return m_pos;
        }

    protected:
        CodePosition m_pos;
    };

    class StmtAST : public AST {
    public:
        static StmtAST *nullStmt() {
            static StmtAST *nullStmt_ = new StmtAST();
            return nullStmt_;
        }

        void accept(ASTVisitor *visitor);

        ~StmtAST() {
        }
    };

    class IfStmtAST : public StmtAST {
    public:
        IfStmtAST(ExprAST *condition_, StmtAST *trueStmt_, StmtAST *elseStmt_) {
            m_condition = condition_;
            m_trueStmt = trueStmt_;
            m_elseStmt = elseStmt_;
        }

        ExprAST *condition() const {
            return m_condition;
        }

        StmtAST *trueStmt() const {
            return m_trueStmt;
        }

        StmtAST *elseStmt() const {
            return m_elseStmt;
        }

        void accept(ASTVisitor *visitor);

    private:
        ExprAST *m_condition;
        StmtAST *m_trueStmt, *m_elseStmt;
    };

    class WhileStmtAST : public StmtAST {
    public:
        WhileStmtAST(ExprAST *condition_, StmtAST *trueStmt_) {
            m_condition = condition_;
            m_trueStmt = trueStmt_;
        }

        ExprAST *condition() const {
            return m_condition;
        }

        StmtAST *trueStmt() const {
            return m_trueStmt;
        }

        void accept(ASTVisitor *);

    private:
        ExprAST *m_condition;
        StmtAST *m_trueStmt;
    };

    class ForStmtAST : public StmtAST {
    public:
        ForStmtAST(ExprAST *init_, ExprAST *condition_, ExprAST *step_, StmtAST *body_) {
            m_init = init_;
            m_condition = condition_;
            m_step = step_;
            m_body = body_;
        }

        ExprAST *init() const {
            return m_init;
        }

        ExprAST *condition() const {
            return m_condition;
        }

        ExprAST *step() const {
            return m_step;
        }

        StmtAST *body() const {
            return m_body;
        }

        void accept(ASTVisitor *);

    private:
        ExprAST *m_init, *m_condition, *m_step;
        StmtAST *m_body;
    };

    class BlockAST : public StmtAST {
    public:
        BlockAST() {
            m_stmtArray = new Array<StmtAST *>();
        }

        ~BlockAST() {
            delete m_stmtArray;
        }

        void append(StmtAST *stmt) {
            m_stmtArray->append(stmt);
        }

        uint size() const {
            return m_stmtArray->size();
        }

        StmtAST *at(uint index) const {
            return m_stmtArray->at(index);
        }

        void accept(ASTVisitor *visitor);

    private:
        Array<StmtAST *> *m_stmtArray;
    };

    class ParamValuePair : public AST {
    public:
        ParamValuePair(const String <char_type> &name_, ExprAST *value_) {
            m_name = name_;
            m_value = value_;
        }

        const String <char_type> &name() const {
            return m_name;
        }

        ExprAST *value() const {
            return m_value;
        }

        ~ParamValuePair() {
        }

    private:
        String <char_type> m_name;
        ExprAST *m_value;
    };

    class DefFuncStmtAST : public StmtAST {
    public:
        DefFuncStmtAST(const String <char_type> &funcName_, Array<ParamValuePair *> *params_, BlockAST *funcBody_) {
            m_funcName = funcName_;
            m_params = params_;
            m_funcBody = funcBody_;
        }

        ~DefFuncStmtAST() {
        }

        void accept(ASTVisitor *visitor);

        const String <char_type> &funcName() const {
            return m_funcName;
        }

        BlockAST *funcBody() const {
            return m_funcBody;
        }

        Array<ParamValuePair *> *params() const {
            return m_params;
        }

    private:
        String <char_type> m_funcName;
        Array<ParamValuePair *> *m_params;
        BlockAST *m_funcBody;
    };

    class PostfixAST : public AST {
    public:
        ~PostfixAST() {
        }

        void accept(ASTVisitor *);
    };

    class ExprAST : public AST {
    public:
        ExprAST() {
            m_postfixes = nullptr;
        }

        ~ExprAST() {
        }

        void accept(ASTVisitor *visitor);

        void appendPostfix(PostfixAST *postfixAST) {
            if (!m_postfixes)
                m_postfixes = new Array<PostfixAST *>();
            m_postfixes->append(postfixAST);
        }

        Array<PostfixAST *> *postfixes() const {
            return m_postfixes;
        }

    private:
        Array<PostfixAST *> *m_postfixes;
    };

    class ExprStmtAST : public StmtAST {
    public:
        ExprStmtAST(ExprAST *expr_) {
            m_expr = expr_;
        }

        void accept(ASTVisitor *visitor);

        virtual ~ExprStmtAST() {
        }

        ExprAST *expr() const {
            return m_expr;
        }

    private:
        ExprAST *m_expr;
    };

    class PrintStmtAST : public StmtAST {
    public:
        PrintStmtAST(ExprAST *expr_) {
            m_expr = expr_;
        }

        virtual    ~PrintStmtAST() {
        }

        ExprAST *expr() {
            return m_expr;
        }

        void accept(ASTVisitor *visitor);

    private:
        ExprAST *m_expr;
    };

    class IndexPostfixAST : public PostfixAST {
    public:
        IndexPostfixAST(ExprAST *indexExpr_, CodePosition pos_) {
            m_indexExpr = indexExpr_;
            m_pos = pos_;
        }

        void accept(ASTVisitor *);

        ExprAST *indexExpr() const {
            return m_indexExpr;
        }

    private:
        ExprAST *m_indexExpr;
    };

    class MemberPostfixAST : public PostfixAST {
    public:
        MemberPostfixAST(const String <char_type> &memberName_) {
            m_memberName = memberName_;
        }

        void accept(ASTVisitor *visitor);

        const String <char_type> &memberName() const {
            return m_memberName;
        }

    private:
        String <char_type> m_memberName;
    };

    class CallFuncPostfixAST : public PostfixAST {
    public:
        CallFuncPostfixAST(Array<ExprAST *> *params_, const CodePosition &pos_) {
            m_pos = pos_;
            m_params = params_;
        }

        void accept(ASTVisitor *visitor);

        Array<ExprAST *> *params() const {
            return m_params;
        }

    private:
        Array<ExprAST *> *m_params;
    };

    class BinaryOpAST : public ExprAST {
    public:
        BinaryOpAST(ExprAST *left_, Operator *op_, ExprAST *right_) {
            m_left = left_;
            m_op = op_;
            m_right = right_;
        }

        virtual ~BinaryOpAST() {

        }

        ExprAST *left() const {
            return m_left;
        }

        ExprAST *right() const {
            return m_right;
        }

        Operator *op() const {
            return m_op;
        }

        void accept(ASTVisitor *visitor);

    private:
        Operator *m_op;
        ExprAST *m_left, *m_right;
    };

    class IntLiteralAST : public ExprAST {
    public:
        IntLiteralAST(const String <char_type> &numString) {
            int res = 0;
            for (uint i = 0; i < numString.size(); i++) {
                res *= 10;
                res += numString[i] - '0';
            }
            m_value = res;
        }

        virtual ~IntLiteralAST() {
        }

        void accept(ASTVisitor *visitor);

        int value() const {
            return m_value;
        }

    private:
        int m_value;
    };

    class ArrayExprAST : public ExprAST {
    public:
        ArrayExprAST(Array<ExprAST *> *exprs_) {
            m_exprs = exprs_;
        }

        virtual ~ArrayExprAST() {
        }

        Array<ExprAST *> *exprs() {
            return m_exprs;
        }

        void accept(ASTVisitor *visitor);

    private:
        Array<ExprAST *> *m_exprs;
    };

    class UnaryOpAST : public ExprAST {
    public:
        UnaryOpAST(Operator *op_, ExprAST *operand_) {
            m_op = op_;
            m_operand = operand_;
        }

        virtual ~UnaryOpAST() {
        }

        Operator *op() const {
            return m_op;
        }

        ExprAST *operand() const {
            return m_operand;
        }

        void accept(ASTVisitor *visitor);

    private:
        Operator *m_op;
        ExprAST *m_operand;
    };

    class VarAST : public ExprAST {
    public:
        virtual ~VarAST() {

        }

        VarAST(const String <char_type> &varName_, CodePosition pos_) {
            m_varName = varName_;
            m_pos = pos_;
        }

        void accept(ASTVisitor *visitor);

        const ds::String<char_type> &varName() const {
            return m_varName;
        }

    private:
        ds::String<char_type> m_varName;
    };

    class ASTVisitor {
    public:
        virtual void visit(AST *) = 0;

        virtual void visit(StmtAST *) = 0;

        virtual void visit(IfStmtAST *) = 0;

        virtual void visit(WhileStmtAST *) = 0;

        virtual void visit(ForStmtAST *) = 0;

        virtual void visit(BlockAST *) = 0;

        virtual void visit(DefFuncStmtAST *) = 0;

        virtual void visit(PostfixAST *) = 0;

        virtual void visit(IndexPostfixAST *) = 0;

        virtual void visit(MemberPostfixAST *) = 0;

        virtual void visit(CallFuncPostfixAST *) = 0;

        virtual void visit(ExprAST *) = 0;

        virtual void visit(ExprStmtAST *) = 0;

        virtual void visit(PrintStmtAST *) = 0;

        virtual void visit(BinaryOpAST *) = 0;

        virtual void visit(IntLiteralAST *) = 0;

        virtual void visit(ArrayExprAST *) = 0;

        virtual void visit(UnaryOpAST *) = 0;

        virtual void visit(VarAST *) = 0;

        ~ASTVisitor() {
        }

    private:
    };

    void AST::accept(ASTVisitor *visitor) {
        visitor->visit(this);
    }

    void StmtAST::accept(ASTVisitor *visitor) {
        visitor->visit(this);
    }

    void IfStmtAST::accept(ASTVisitor *visitor) {
        visitor->visit(this);
    }

    void WhileStmtAST::accept(ASTVisitor *visitor) {
        visitor->visit(this);
    }

    void ForStmtAST::accept(ASTVisitor *visitor) {
        visitor->visit(this);
    }

    void BlockAST::accept(ASTVisitor *visitor) {
        visitor->visit(this);
    }

    void DefFuncStmtAST::accept(ASTVisitor *visitor) {
        visitor->visit(this);
    }

    void ExprAST::accept(ASTVisitor *visitor) {
        visitor->visit(this);
    }

    void PostfixAST::accept(ASTVisitor *visitor) {
        visitor->visit(this);
    }

    void IndexPostfixAST::accept(ASTVisitor *visitor) {
        visitor->visit(this);
    }

    void MemberPostfixAST::accept(ASTVisitor *visitor) {
        visitor->visit(this);
    }

    void CallFuncPostfixAST::accept(ASTVisitor *visitor) {
        visitor->visit(this);
    }

    void ExprStmtAST::accept(ASTVisitor *visitor) {
        visitor->visit(this);
    }

    void PrintStmtAST::accept(ASTVisitor *visitor) {
        visitor->visit(this);
    }

    void BinaryOpAST::accept(ASTVisitor *visitor) {
        visitor->visit(this);
    }

    void UnaryOpAST::accept(ASTVisitor *visitor) {
        visitor->visit(this);
    }

    void IntLiteralAST::accept(ASTVisitor *visitor) {
        visitor->visit(this);
    }

    void ArrayExprAST::accept(ASTVisitor *visitor) {
        visitor->visit(this);
    }

    void VarAST::accept(ASTVisitor *visitor) {
        visitor->visit(this);
    }
}
