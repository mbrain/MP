#ifndef NODE_H
#define NODE_H

#include <vector>
#include <string>
#include <iostream>
#include <cmath>

class Node
{
    public:
        virtual ~Node() { }

        virtual double eval() const = 0;
}; 

class NodeNumber : public Node
{
    private:
        double myVal;

    public:
        NodeNumber(double val) : myVal(val) { }

        virtual double eval() const { return myVal; }
}; 

class NodeAdd : public Node
{
    private:
        Node *myNodeLeft;
        Node *myNodeRight;

    public:
        NodeAdd(Node *left, Node *right) : myNodeLeft(left), myNodeRight(right) { }
       
        virtual ~NodeAdd()
        {
            delete myNodeLeft;
            delete myNodeRight;
        }

        virtual double eval() const { return myNodeLeft->eval() + myNodeRight->eval(); }
}; 

class NodeMul : public Node
{
    private:
        Node *myNodeLeft;
        Node *myNodeRight;

    public:
        NodeMul(Node *left, Node *right) : myNodeLeft(left), myNodeRight(right) { }
       
        virtual ~NodeMul()
        {
            delete myNodeLeft;
            delete myNodeRight;
        }

        virtual double eval() const { return myNodeLeft->eval() * myNodeRight->eval(); }
}; 

class NodeMod : public Node
{
    private:
        Node *myNodeLeft;
        Node *myNodeRight;

    public:
        NodeMod(Node *left, Node *right) : myNodeLeft(left), myNodeRight(right) { }
       
        virtual ~NodeMod()
        {
            delete myNodeLeft;
            delete myNodeRight;
        }

        virtual double eval() const { return (int)myNodeLeft->eval() % (int)myNodeRight->eval(); }
}; 

class NodePow : public Node
{
    private:
        Node *myNodeLeft;
        Node *myNodeRight;

    public:
        NodePow(Node *left, Node *right) : myNodeLeft(left), myNodeRight(right) { }
       
        virtual ~NodePow()
        {
            delete myNodeLeft;
            delete myNodeRight;
        }

        virtual double eval() const { return pow( (int)myNodeLeft->eval(),(int)myNodeRight->eval()); }
};

class NodeSub : public Node
{
    private:
        Node *myNodeLeft;
        Node *myNodeRight;

    public:
        NodeSub(Node *left, Node *right) : myNodeLeft(left), myNodeRight(right) { }
       
        virtual ~NodeSub()
        {
            delete myNodeLeft;
            delete myNodeRight;
        }

        virtual double eval() const { return myNodeLeft->eval() - myNodeRight->eval(); }
}; 

class NodeDiv : public Node
{
    private:
        Node *myNodeLeft;
        Node *myNodeRight;

    public:
        NodeDiv(Node *left, Node *right) : myNodeLeft(left), myNodeRight(right) { }
       
        virtual ~NodeDiv()
        {
            delete myNodeLeft;
            delete myNodeRight;
        }

		virtual double eval() const
		{
			double right = myNodeRight->eval();

			if (right != 0)
			{
				return myNodeLeft->eval() / right;
			}

			std::cerr << "Error: Division durch 0" << std::endl;

			return 1;
		} 
}; 

class NodeIdent : public Node
{
	private:
		std::string myName;

	public:
		NodeIdent(const std::string& name) : myName(name) { }

		const std::string& getName() const { return myName; }

		virtual double eval() const 
		{
			if (myName == "pi")
			{
				return 3.1415926535897932384626433832795;
			}
			else if (myName == "c")
			{
				return 299792458;
			}
			else if (myName == "e")
			{
				return 2.7182818284504523536028747135266;
			}

			std::cerr << "Error: unbekannte Konstante '" << myName << "'" << std::endl;

			return 1;
		}
};

typedef std::vector<Node *> ArgVec;

class NodeFunc : public Node
{
	private:
		NodeIdent *myIdent;
		ArgVec myArgs;

	public:
		NodeFunc(NodeIdent *ident) : myIdent(ident) { }

		virtual ~NodeFunc()
		{
			for (ArgVec::iterator it = myArgs.begin(); it != myArgs.end(); ++it)
			{
				delete *it;
			}

			delete myIdent;
		}

		void pushArg(Node *node) { myArgs.push_back(node); }
		
		bool checkArgCount(unsigned int count) const
		{
			if (myArgs.size() != count)
			{
				std::cerr << "Error: Funktion '" << myIdent->getName() << "' erwartet '" << count << "' Parameter" << std::endl;

				return false;
			}

			return true;
		}

		virtual double eval() const 
		{ 
			if (myIdent->getName() == "sin")
			{
				if (checkArgCount(1))
				{
					return sin(myArgs[0]->eval());
				}
			}
			else if (myIdent->getName() == "cos")
			{
				if (checkArgCount(1))
				{
					return cos(myArgs[0]->eval());
				}
			}
			else if (myIdent->getName() == "tan")
			{
				if (checkArgCount(1))
				{
					return tan(myArgs[0]->eval());
				}
			}
			else if (myIdent->getName() == "sqrt")
			{
				if (checkArgCount(1))
				{
					return sqrt(myArgs[0]->eval());
				}
			}
			else if (myIdent->getName() == "pow")
			{
				if (checkArgCount(2))
				{
					return pow(myArgs[0]->eval(), myArgs[1]->eval());
				}
			}
			else
			{
				std::cerr << "Error: unbekannte Funktion '" << myIdent->getName() << "'" << std::endl;
			}

			return 1;
		}
};

#endif /* NODE_H */