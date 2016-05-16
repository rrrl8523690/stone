#pragma once

#include <iostream>
namespace test {
	class Visitor;
	class Node {
	public:
		virtual void accept(Visitor *visitor) = 0;
	};

	class Node1;
	class Node2;
	class Visitor {
	public:
		virtual void visit(Node *) = 0;
		virtual void visit(Node1 *) = 0;
		virtual void visit(Node2 *) = 0;
	};

	class Node1 : virtual public Node {
	public:
		void accept(Visitor *visitor) {
			visitor->visit(this);
		}
	};

	class Node2 : virtual public Node {
	public:
		void accept(Visitor *visitor) {
			visitor->visit(this);
		}
	};



	class Visitor1 : virtual public Visitor {
	public:
		void visit(Node*) {
			std::cerr << "visitor1 is visiting Node" << std::endl;
		}
		void visit(Node1*) {
			std::cerr << "visitor1 is visiting Node1" << std::endl;
		}
		void visit(Node2*) {
			std::cerr << "visitor1 is visiting Node2" << std::endl;
		}
	};
}