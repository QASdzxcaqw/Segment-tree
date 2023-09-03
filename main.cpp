#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <cmath>
#include <set>

struct Segment {
    int start; // The start point of the interval represented by this node
    int end;   // The end point of the interval represented by this node
    std::string segmentName; // Names of line segments that cover this interval
    bool flag;
    Segment(int s, int e, std::string name) : start(s), end(e), segmentName(name)  {}

};



struct TreeNode {
    int start; // The start point of the interval represented by this node
    int end;   // The end point of the interval represented by this node
    std::list<Segment> segmentNames; // Names of line segments that cover this interval
    bool mark;
    TreeNode(int s, int e) : start(s), end(e) {}
};

class SegmentTree {
private:
    std::vector<TreeNode> nodes;
    int h; // Depth of the tree
    std::vector<int> endpoints;
    std::vector<Segment> segments;


public:
    SegmentTree(int h, std::vector<Segment> segments ) : h(h), segments(segments) {
        //nodes.resize((1 << (h + 1)) - 1, TreeNode(0, 0));
        //buildTree(0, 0, endpoints.size()-1, endpoints);
    }


    void buildTree(int nodeIndex, int start, int end) {
        if (start > end) {
            return;
        }
        nodes[nodeIndex].start = endpoints[start];
        nodes[nodeIndex].end = endpoints[end];
        if ( end >= endpoints.size()) {
            nodes[nodeIndex].mark == true;
            nodes[nodeIndex].start = 0;
            nodes[nodeIndex].end = 0;
        }
        for(auto i: segments){
            if (nodes[nodeIndex].start >= i.start && nodes[nodeIndex].end <= i.end &&
            nodes[nodeIndex].start != nodes[nodeIndex].end && nodes[nodeIndex].mark != true) {
                if (check(nodes[nodeIndex].segmentNames, i)){
                    std::cout<<nodeIndex;
                    nodes[nodeIndex].segmentNames.pop_back();
                }else {
                    nodes[nodeIndex].segmentNames.push_back(i);
                }
            }
        }

        if (start < end) {
            int mid;
            mid = start + (end - start) / 2;
            buildTree(2 * nodeIndex + 1, start, mid);     // Build left subtree
            buildTree(2 * nodeIndex + 2, mid +1, end);  // Build right subtree
        }
    }
    bool check(std::list<Segment> segmentNames, Segment s){
         for(auto it: segmentNames){
             if (it.segmentName == s.segmentName)
                 return true;
         }
         return false;

    }
    void insertSegments(){
        for(auto i: segments){
            endpoints.push_back(i.start);
            endpoints.push_back(i.end);
        }

        std::sort(endpoints.begin(), endpoints.end());
        std::set<int> int_set(endpoints.begin(), endpoints.end());
        endpoints.assign(int_set.begin(), int_set.end());
        h = ceil(log2(endpoints.size()));
        nodes.resize((1 << (h + 1)) - 1, TreeNode(0, 0));
        buildTree(0, 0, std::pow(2, h) - 1);
    }
//    void insertSegment(int nodeIndex, int segmentStart, int segmentEnd, const std::string& segmentName) {
//          endpoints.push_back()
//        if (nodes[nodeIndex].start >= segmentStart && nodes[nodeIndex].end <= segmentEnd && nodes[nodeIndex].start != nodes[nodeIndex].end) {
//            nodes[nodeIndex].segmentNames.push_back(segmentName);
//            //return;
//        }
//
//        if (nodes[nodeIndex].start >= segmentEnd || nodes[nodeIndex].end <= segmentStart) {
//            return; // No overlap, stop here
//        }
//
//        insertSegment(2 * nodeIndex + 1, segmentStart, segmentEnd, segmentName); // Update left child
//        insertSegment(2 * nodeIndex + 2, segmentStart, segmentEnd, segmentName); // Update right child
//    }

//    void removeSegment(int nodeIndex, const std::string& segmentName) {
//        nodes[nodeIndex].segmentNames.remove(segmentName);
//
//        if (nodes[nodeIndex].start == nodes[nodeIndex].end) {
//            return; // Leaf node
//        }
//
//        removeSegment(2 * nodeIndex + 1, segmentName); // Remove from left child
//        removeSegment(2 * nodeIndex + 2, segmentName); // Remove from right child
//    }

    void printTree(int nodeIndex = 0, int level = 0) {
        if (nodeIndex >= nodes.size()) {
            return;
        }

        for (int i = 0; i < level; ++i) {
            std::cout << "  ";
        }

        std::cout << "|- Node: [" << nodes[nodeIndex].start << ", " << nodes[nodeIndex].end << "]"
                  << " Segments: ";
        for (auto name : nodes[nodeIndex].segmentNames) {
            std::cout << name.segmentName << " ";
        }
        std::cout << std::endl;

        printTree(2 * nodeIndex + 1, level + 1); // Print left child
        printTree(2 * nodeIndex + 2, level + 1); // Print right child
    }


};


int main() {
    int h = 1; // Depth of the tree
    //std::vector<int> endpoints = {3, 6, 8, 11, 14, 15, 19, 21, 23, 27, 34, 36};


    Segment A(6, 36, "A");
    Segment B(34, 38, "B");
    Segment C(21, 36, "C");
    Segment D(23, 27, "D");
    Segment E(3, 8, "E");
    Segment F(15, 19, "F");
    Segment G(11, 14, "G");

    std::vector<Segment> segments;
    segments.push_back(A);
    segments.push_back(B);
    segments.push_back(C);
    segments.push_back(D);
    segments.push_back(E);
    segments.push_back(F);
    segments.push_back(G);
    SegmentTree tree(h, segments);
//    tree.insertSegment(0, 3, 11, "A");
//    tree.insertSegment(0, 8, 27, "B");
//    tree.insertSegment(0, 14, 38, "C");
    tree.insertSegments();
    tree.printTree();
    //tree.removeSegment(0, "B");
    //tree.printTree();

    return 0;
}
