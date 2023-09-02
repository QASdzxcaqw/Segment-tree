#include <iostream>
#include <vector>
#include <list>

struct TreeNode {
    int start; // The start point of the interval represented by this node
    int end;   // The end point of the interval represented by this node
    std::list<std::string> segmentNames; // Names of line segments that cover this interval

    TreeNode(int s, int e) : start(s), end(e) {}
};

class SegmentTree {
private:
    std::vector<TreeNode> nodes;
    int h; // Depth of the tree

public:
    SegmentTree(int h, const std::vector<int>& endpoints) : h(h) {
        nodes.resize((1 << (h + 1)) - 1, TreeNode(0, 0));
        buildTree(0, 0, endpoints.size()-1, endpoints);
    }


    void buildTree(int nodeIndex, int start, int end, const std::vector<int>& endpoints) {
        if (start > end) {
            return;
        }

        nodes[nodeIndex].start = endpoints[start];
        nodes[nodeIndex].end = endpoints[end];

        if (start < end) {
            int mid = start + (end - start) / 2;
            buildTree(2 * nodeIndex + 1, start, mid, endpoints);     // Build left subtree
            buildTree(2 * nodeIndex + 2, mid + 1, end, endpoints);  // Build right subtree
        }
    }

    void insertSegment(int nodeIndex, int segmentStart, int segmentEnd, const std::string& segmentName) {
        if (nodes[nodeIndex].start >= segmentStart && nodes[nodeIndex].end <= segmentEnd && nodes[nodeIndex].start != nodes[nodeIndex].end) {
            nodes[nodeIndex].segmentNames.push_back(segmentName);
            //return;
        }

        if (nodes[nodeIndex].start >= segmentEnd || nodes[nodeIndex].end <= segmentStart) {
            return; // No overlap, stop here
        }

        insertSegment(2 * nodeIndex + 1, segmentStart, segmentEnd, segmentName); // Update left child
        insertSegment(2 * nodeIndex + 2, segmentStart, segmentEnd, segmentName); // Update right child
    }

    void removeSegment(int nodeIndex, const std::string& segmentName) {
        nodes[nodeIndex].segmentNames.remove(segmentName);

        if (nodes[nodeIndex].start == nodes[nodeIndex].end) {
            return; // Leaf node
        }

        removeSegment(2 * nodeIndex + 1, segmentName); // Remove from left child
        removeSegment(2 * nodeIndex + 2, segmentName); // Remove from right child
    }

    void printTree(int nodeIndex = 0, int level = 0) {
        if (nodeIndex >= nodes.size()) {
            return;
        }

        for (int i = 0; i < level; ++i) {
            std::cout << "  ";
        }

        std::cout << "|- Node: [" << nodes[nodeIndex].start << ", " << nodes[nodeIndex].end << "]"
                  << " Segments: ";
        for (const std::string& name : nodes[nodeIndex].segmentNames) {
            std::cout << name << " ";
        }
        std::cout << std::endl;

        printTree(2 * nodeIndex + 1, level + 1); // Print left child
        printTree(2 * nodeIndex + 2, level + 1); // Print right child
    }


};


int main() {
    int h = 4; // Depth of the tree
    std::vector<int> endpoints = {3, 6, 8, 11, 14, 15, 19, 21, 23, 27, 34, 36};

    SegmentTree tree(h, endpoints);

//    tree.insertSegment(0, 3, 11, "A");
//    tree.insertSegment(0, 8, 27, "B");
//    tree.insertSegment(0, 14, 38, "C");

    tree.printTree();
    //tree.removeSegment(0, "B");
    //tree.printTree();

    return 0;
}
