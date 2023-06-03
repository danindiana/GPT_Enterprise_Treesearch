module IterativeDeepening {
  /* Your code goes here */

  proc DLS(node, depth, maxDepth): bool {
    if depth > maxDepth { // we've reached the maximum depth
      return false;
    }

    if node is Target { // check if node is the one we're looking for
      return true;
    }

    for child in node.getChildren() {
      if DLS(child, depth + 1, maxDepth) {
        return true;
      }
    }

    return false;
  }

  proc IDDFS(root, maxDepth) {
    for depth in 0..maxDepth {
      if DLS(root, 0, depth) {
        return true;
      }
    }
    return false;
  }
}
