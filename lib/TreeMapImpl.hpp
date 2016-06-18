#pragma once

#include "Map.hpp"
#include "stdafx.h"
#include <memory>

namespace ds {
	template<class KeyType, class ValueType>
	class TreeMapImpl {
	public:
		TreeMapImpl() {
			m_root = SBTNode::nul();
		}
		~TreeMapImpl() {
		}
		void insert(const KeyType &key, const ValueType &value) {

		}
	private:
		class SBTNode {
		public:
			typedef std::shared_ptr<SBTNode> NodePtr;
			SBTNode() {
				child[0] = child[1] = nullptr;
				key = nullptr;
				value = nullptr;
				size = 0;
			}
			~TreeMapImpl() {
				delete key;
				delete value;
			}

			NodePtr child[2];
			KeyType *key;
			ValueType *value;
			uint size;
		};
		typedef SBTNode::NodePtr NodePtr;
		NodePtr nul() {
			static NodePtr nul_;
			if (!nul_) {
				nul_ = new SBTNode();
				nul_->child[0] = nul_->child[1] = nul_;
				nul_->size = 0;
			}
			return nul_;
		}
		NodePtr newNode() {
			NodePtr ptr = new SBTNode();
			ptr->child[0] = ptr->child[1] = SBTNode::nul();
			return ptr;
		}
		inline void rotate(NodePtr &t, bool d) {
			using std::shared_ptr;
			shared_ptr<SBTNode> p = t->child[!d];
			t->child[!d] = p->child[d];
			p->child[d] = t;
			p->size = t->size;
			t->size = t->child[0]->size + t->child[1]->size + 1;
			t = p;
		}
		void maintain(SBTNode::NodePtr &t, bool d) {
			if (!t)
				return;
			if (t->child[d]->child[d]->size > t->child[!d]->size)
				rotate(t, !d);
			else if (t->child[d]->child[!d]->size > t->child[!d]->size) {
				rotate(t->child[d], d);
				rotate(t, !d);
			} else
				return;
			maintain(t->child[0], 0);
			maintain(t->child[1], 1);
			maintain(t, 0);
			maintain(t, 1);
		}
		void insert(SBTNode::NodePtr &t, const KeyType &key, const ValueType &value) {
			if (t == nul) {
				t = n
			}
		}
		SBTNode::NodePtr del(std::shared_ptr<SBTNode> &t, const KeyType &key) {

		}
		std::shared_ptr<SBTNode> m_root;
	};
}