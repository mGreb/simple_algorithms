#include <iostream>
#include <functional>
#include <stack>
#include <cassert>
#include <set>
#include <algorithm>
#include <numeric>

static const bool RUN_TEST = false;

using val_t = long long;

template<typename T>
T readT(std::istream& is = std::cin) {
    T val;
    is >> val;
    return val;
}

struct node {
    val_t val;
    val_t sum;
    val_t h;
    node* parent;
    node* left;
    node* right;

    void deleteChild(node* n) {
        if (left == n) {
            left = nullptr;
            return;
        }
        if (right == n) {
            right = nullptr;
            return;
        }
        throw std::runtime_error("Trying to delete non child node!");
    }

    static val_t getBalanceFactor(node* n) {
        if (n) {
            return getHeight(n->left) - getHeight(n->right);
        } else {
            return 0;
        }
    }

    static void updateSum(node* n) {
        while (n) {
            val_t sum = n->val;
            if (n->left) {
                sum += n->left->sum;
            }
            if (n->right) {
                sum += n->right->sum;
            }
            n->sum = sum;
            n = n->parent;
        }
    }

    static void updateHeight(node* n) {
        while (n) {
            n->h = std::max(getHeight(n->left), getHeight(n->right)) + 1;
            n = n->parent;
        }
    }

    static val_t getHeight(node* n) {
        if (n) {
            return n->h;
        } else {
            return 0;
        }
    }

    static bool isLeaf(node* n) {
        return n->left == nullptr && n->right == nullptr;
    }

    static node* createNode(val_t val, val_t sum = 0, val_t h = 0) {
        return new node{val, sum, h, nullptr, nullptr, nullptr};
    }

    static void deleteNode(node* n) {
        delete n;
    }
};

class tree {
    node* root;
    void rightRotate(node* n) {
        node* a = n;
        node* b = n->left;

        if (a->parent) {
            if (a->parent->left == a) {
                a->parent->left = b;
            } else {
                a->parent->right = b;
            }
        } else {
            this->root = b;
        }

        b->parent = a->parent;
        a->parent = b;

        if (b->right) {
            b->right->parent = a;
        }
        a->left = b->right;
        b->right = a;

        node::updateHeight(a);
        node::updateSum(a);
    }
    void leftRotate(node* n) {
        node* a = n;
        node* b = n->right;
        
        if (a->parent) {
            if (a->parent->left == a) {
                a->parent->left = b;
            } else {
                a->parent->right = b;
            }
        } else {
            this->root = b;
        }

        b->parent = a->parent;
        a->parent = b;

        if (b->left) {
            b->left->parent = a;
        }
        a->right = b->left;
        b->left = a;

        node::updateHeight(a);
        node::updateSum(a);
    }
    void goUpAndRestoreBalance(node* n) {
        while (n) {
            const val_t bf = node::getBalanceFactor(n);
            if (bf > 1) {
                if (node::getBalanceFactor(n->left) >= 0) {
                    rightRotate(n);
                } else {
                    leftRotate(n->left);
                    rightRotate(n);
                }
            }
            if (bf < -1) {
                if (node::getBalanceFactor(n->right) <= 0) {
                    leftRotate(n);
                } else {
                    rightRotate(n->right);
                    leftRotate(n);
                }
            }
            n = n->parent;
        }
        testSelf();
    }
    void applyOpOnRoute(val_t i, const std::function<void(node*, val_t)>& op) {
        auto curr = root;
        while (curr != nullptr) {
            if (curr->val == i) {
                op(curr, i);
                return;
            }
            if (i > curr->val) {
                op(curr, i);
                curr = curr->right;
                continue;
            }
            if (i < curr->val) {
                op(curr, i);
                curr = curr->left;
                continue;
            }
        }
    }
    void remI(val_t i) {
        const auto op = [](node* n, val_t x) {
            n->sum -= x;
        };
        applyOpOnRoute(i, op);
    }
    void addI(val_t i) {
        const auto op = [](node* n, val_t x) {
            n->sum += x;
        };
        applyOpOnRoute(i, op);
    }
    node* floor(val_t i) {
        auto curr = root;
        node* prev = nullptr;
        while (curr) {
            if (curr->val == i) {
                return curr;
            }
            if (curr->val > i) {
                prev = curr;
                curr = curr->left;
            } else {
                curr = curr->right;
            }
        }
        return prev;
    }
    node* ceil(val_t i) {
        auto curr = root;
        node* prev = nullptr;
        while (curr) {
            if (curr->val == i) {
                return curr;
            }
            if (curr->val < i) {
                prev = curr;
                curr = curr->right;
            } else {
                curr = curr->left;
            }
        }
        return prev;
    }
    node* findNode(val_t i) {
        auto curr = root;
        while (curr) {
            if (curr->val == i) {
                return curr;
            }
            if (i > curr->val) {
                curr = curr->right;
                continue;
            }
            if (i < curr->val) {
                curr = curr->left;
                continue;
            }
        }
        return nullptr;
    }
    void deleteNode(node* n) {
        delete n;
        if (n == root) {
            root = nullptr;
        }
    }
    node* findLCA(node* p, node* q) {
        if (!root || !p || !q) {
            return nullptr;
        }
        node* curr = root;
        while (curr) {
            if (p->val < curr->val && q->val < curr->val) {
                curr = curr->left;
            } else {
                if (p->val > curr->val && q->val > curr->val) {
                    curr = curr->right;
                } else {
                    return curr;
                }
            }
        }
        throw std::runtime_error("We shouldn`t be here!");
    }
    void testSelfImpl(node* curr) {
        if (!curr) {
            return;
        }
        if (curr->left) {
            assert(curr->val > curr->left->val);
            assert(curr->left->parent == curr);
        }
        if (curr->right) {
            assert(curr->val < curr->right->val);
            assert(curr->right->parent == curr);
        }
        if (curr->parent) {
            assert(curr->parent->left == curr || curr->parent->right == curr);
        }
        if (curr->left && curr->right) {
            assert(curr->sum - curr->val == curr->left->sum + curr->right->sum);
        }
        if (curr->left && !curr->right) {
            assert(curr->sum - curr->val == curr->left->sum);
        }
        if (!curr->left && curr->right) {
            assert(curr->sum - curr->val == curr->right->sum);
        }
        if (!curr->left && ! curr->right) {
            assert(curr->sum == curr->val);
        }
        testSelfImpl(curr->left);
        testSelfImpl(curr->right);
    }
    val_t testSumImpl(node* n) {
        if (!n) {
            return 0;
        }
        val_t leftSum = testSumImpl(n->left);
        val_t rightSum = testSumImpl(n->right);
        if (n->left) {
            assert(n->left->sum == leftSum);
        }
        if (n->right) {
            assert(n->right->sum == rightSum);
        }
        val_t res = n->val + leftSum + rightSum;
        assert(n->sum == res);
        return res;
    }
    int testHeightImpl(node* n) {
        if (n) {
            int heightL = testHeightImpl(n->left);
            int heightR = testHeightImpl(n->right);
            int height = std::max(heightL, heightR) + 1;
            assert(n->h == height);
            return height;
        } else {
            return 0;
        }
    }
    void testBalanceImpl(node* n) {
        if (n) {
            const auto bf = node::getBalanceFactor(n);
            assert(bf >= -1 && bf <= 1);
            testBalanceImpl(n->left);
            testBalanceImpl(n->right);
        } else {
            return;
        }
    }
public:
    void inOrder(const std::function<void(node*)>& op) {
        std::stack<node*> s;
        auto curr = root;
        while (curr != nullptr || !s.empty()) {
            while (curr != nullptr) {
                s.push(curr);
                curr = curr->left;
            }
            curr = s.top();
            s.pop();
            op(curr);
            curr = curr->right;
        }
    }
    tree(): root(nullptr) {}
    tree(node* root_): root(root_) {}
    ~tree() {
        inOrder([this] (node* n) {this->deleteNode(n);});
    }
    void testSelf() {
        if (RUN_TEST) {
            testSelfImpl(root);

            const val_t compSum = testSumImpl(root);
            assert((root ? root->sum : 0) == compSum);
    
            testHeightImpl(root);
            testBalanceImpl(root);
    
            // BST check
            std::vector<val_t> res;
            inOrder([&res](node* n) {res.push_back(n->val);});
            std::vector<val_t> resSorted = res;
            std::sort(resSorted.begin(), resSorted.end());
            assert(res == resSorted);
        }
    }
    void insert(val_t i) {
        node* curr = root;
        node* prev = nullptr;
        while (curr != nullptr) {
            if (i > curr->val) {
                prev = curr;
                curr = curr->right;
                continue;
            }
            if (i < curr->val) {
                prev = curr;
                curr = curr->left;
                continue;
            }
            if (i == curr->val) {
                return;
            }
        }
        node* newNode = node::createNode(i);
        newNode->parent = prev;
        if (prev) {
            if (!prev->left && i < prev->val) {
                prev->left = newNode;
            } else {
                prev->right = newNode;
            }
        } else {
            root = newNode;
        }
        addI(newNode->val);
        node::updateHeight(newNode);
        goUpAndRestoreBalance(newNode->parent);
        testSelf();
    }
    void remove(val_t i) {
        node* n = findNode(i);
        if (n) {
            if (node::isLeaf(n)) {
                remI(n->val);
                if (n->parent) {
                    n->parent->deleteChild(n);
                    node::updateHeight(n->parent);
                    goUpAndRestoreBalance(n->parent);
                }
                deleteNode(n);
                testSelf();
                return;
            }
            if ((!n->left && n->right) || (n->left && !n->right)) {  // one child
                remI(n->val);
                node* child = n->right ? n->right : n->left;
                n->val = child->val;
                n->left = child->left;
                n->right = child->right;
                if (n->left) {
                    n->left->parent = n;
                }
                if (n->right) {
                    n->right->parent = n;
                }
                node::updateHeight(n);
                goUpAndRestoreBalance(n);
                deleteNode(child);
                testSelf();
                return;
            }
            if (n->left && n->right) {
                node* minRight = n->right;
                while (minRight->left) {  // get min element in right subtree
                    minRight = minRight->left;
                }
                remI(minRight->val);  // we are going to delete minRight, so subtract it from the tree
                
                if (node::isLeaf(minRight)) {  // min node is leaf node
                    remI(n->val);
                    n->val = minRight->val;
                    addI(n->val);
                    
                    if (minRight->parent) {
                        minRight->parent->deleteChild(minRight);
                        node::updateHeight(minRight->parent);
                        goUpAndRestoreBalance(minRight->parent);
                    }
                    deleteNode(minRight);
                    testSelf();
                } else {  // minRight has right child
                    remI(n->val);
                    n->val = minRight->val;
                    addI(n->val);
                    
                    minRight->right->parent = minRight->parent;  // exclude minRight from parents
                    
                    if (minRight->parent->left == minRight) {  // exclude minRight from child
                        minRight->parent->left = minRight->right;
                    } else {
                        minRight->parent->right = minRight->right;
                    }
                    if (minRight->parent) {
                        node::updateHeight(minRight->parent);
                        goUpAndRestoreBalance(minRight->parent);
                    }
                    deleteNode(minRight);
                    testSelf();
                }
                testSelf();
                return;
            }
        }
    }
    bool find(val_t i) {
        return findNode(i) != nullptr;
    }
    val_t sumImpl(node* lower, node* upper, node* lca) {
        val_t sum = lca->sum;
        node* curr = lca;
        while (true) {
            if (curr->val < lower->val) {
                if (curr->left) {
                    sum -= curr->left->sum;
                }
                sum -= curr->val;
                curr = curr->right;
                continue;
            }
            if (curr->val > lower->val) {
                curr = curr->left;
                continue;
            }
            if (curr->val == lower->val) {
                if (curr->left) {
                    sum -= curr->left->sum;
                }
                break;
            }
        }
        curr = lca;
        while (true) {
            if (curr->val < upper->val) {
                curr = curr->right;
                continue;
            }
            if (curr->val > upper->val) {
                if (curr->right) {
                    sum -= curr->right->sum;
                }
                sum -= curr->val;
                curr = curr->left;
                continue;
            }
            if (curr->val == upper->val) {
                if (curr->right) {
                    sum -= curr->right->sum;
                }
                break;
            }
        }
        testSelf();
        return sum;
    }
    val_t sum(val_t l, val_t r) {
        if (l > r) {
            return 0;
        }
        node* lower = floor(l);
        if (!lower) {
            return 0;
        }
        node* upper = ceil(r);
        if (!upper) {
            return 0;
        }
        node* lca = findLCA(lower, upper);
        if (!lca) {
            return 0;
        }
        
        return sumImpl(lower, upper, lca);
    }
};

val_t f(val_t s, val_t i) {
    static const val_t big = 1'000'000'001;
    return (i + s) % big;
}

tree createTree() {
    node* root = node::createNode(100, 550, 3);
    root->left = node::createNode(98, 247, 2); root->right = node::createNode(101, 203, 2);
    root->left->parent = root; root->right->parent = root;
    root->left->left = node::createNode(50, 50, 1); root->left->right = node::createNode(99, 99, 1);
    root->left->left->parent = root->left;
    root->left->right->parent = root->left;
    root->right->right = node::createNode(102, 102, 1);
    root->right->right->parent = root->right;
    auto t = tree(root);
    t.testSelf();
    return t;
}

void test() {
    {
        auto t = createTree();
        assert(!t.find(0));
        assert(t.find(100));
        assert(t.find(101));
        assert(t.find(98));
        assert(t.find(50));
        assert(t.find(99));
        t.testSelf();
    }
    {
        auto t = createTree();
        t.remove(50);
        t.remove(102);
        t.remove(98);
        t.remove(-1);
        t.remove(101);
        t.remove(100);
        t.remove(99);
        t.remove(-1);
    }
    {
        auto t = createTree();
        t.remove(100);
        assert(298 == t.sum(51, 101));
        assert(101 == t.sum(101, 101));
        t.remove(101);
        assert(102 == t.sum(102,132));
        t.remove(102);
        t.remove(98);
        t.remove(99);
        t.remove(50);
    }
    {
        tree t;
        t.insert(100);
        assert(100 == t.sum(10, 101));
        t.insert(98);
        t.insert(101);
        t.insert(102);
        t.insert(50);
        t.insert(99);
        assert(398 == t.sum(51, 101));
    }
    {
        auto t = createTree();
        assert(398 == t.sum(51, 101));
        assert(100 == t.sum(100, 100));
        assert(550 == t.sum(50, 102));
        assert(550 == t.sum(49, 103));
        assert(500 == t.sum(98, 102));
        assert(0 == t.sum(100, 99));
    }
    {
        val_t s = 0;
        tree t;
        t.find(f(s,1));
        t.insert(f(s,1));
        t.find(f(s,1));
        t.insert(f(s,2));
        t.sum(f(s,1), f(s,2));
        t.insert(f(s,1000000000));
        t.find(f(s,1000000000));
        t.remove(f(s,1000000000));
        t.find(f(s,1000000000));
        t.sum(f(s,999999999), f(s,1000000000));
        t.remove(f(s,2));
        t.find(f(s,2));
        t.remove(f(s,0));
        t.insert(f(s,9));
        t.sum(f(s,0), f(s,9));
    }
    {
        srand( (unsigned)time(NULL) );
        std::set<val_t> values;
        tree t; 
        for (size_t i = 0; i < 1'000'000; ++i) {
            int n = rand() % 100;
            t.insert(n); values.emplace(n);
            n = rand() % 100;
            t.remove(n); values.erase(n);
            n = rand() % 100;
            if (t.find(n) != values.count(n)) {
                std::cout << i << "\n";
            }
            val_t n1 = rand() % 1000; val_t n2 = rand() % 1000;
            val_t sum1 = t.sum(n1, n2);
            val_t sum2 = std::accumulate(values.begin(), values.end(), 0, [n1, n2](val_t sum, val_t node){
                if (node >= n1 && node <= n2) {
                    return sum + node;
                } else {
                    return sum;
                }
            });
            std::vector<val_t> res;
            t.inOrder([&res](node* n) {res.push_back(n->val);});
            std::vector<val_t> resSorted = res;
            std::sort(resSorted.begin(), resSorted.end());
            assert(res == resSorted);
            val_t sum3 = std::accumulate(res.begin(), res.end(), 0, [n1, n2](val_t sum, val_t node){
                if (node >= n1 && node <= n2) {
                    return sum + node;
                } else {
                    return sum;
                }
            });
            if (sum1 != sum2 || sum1 != sum3) {
                std::cout << "Sum fail\n";
            }
        }
    }
}

int main() {
    if (RUN_TEST) {
        test();
    } else {
        const auto n = readT<size_t>();
        auto t = tree();
        val_t s = 0;
        for (size_t i = 0; i < n; ++i) {
            const auto command = readT<std::string>();
            if (command == "+") {
                const auto i = readT<val_t>();
                t.insert(f(s, i));
            }
            if (command == "-") {
                const auto i = readT<val_t>();
                t.remove(f(s, i));
            }
            if (command == "?") {
                const auto i = readT<val_t>();
                if (t.find(f(s, i))) {
                    std::cout << "Found\n";
                } else {
                    std::cout << "Not found\n";
                }
            }
            if (command == "s") {
                const auto l = readT<val_t>();
                const auto r = readT<val_t>();
                s = t.sum(f(s, l), f(s, r));
                std::cout << s << "\n";
            }
        }
    }
    return 0;
}