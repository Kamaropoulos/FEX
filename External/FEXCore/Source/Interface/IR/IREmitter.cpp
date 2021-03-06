#include <FEXCore/IR/IREmitter.h>

namespace FEXCore::IR {
void IREmitter::ResetWorkingList() {
  Data.Reset();
  ListData.Reset();
  CodeBlocks.clear();
  CurrentWriteCursor = nullptr;
  // This is necessary since we do "null" pointer checks
  InvalidNode = reinterpret_cast<OrderedNode*>(ListData.Allocate(sizeof(OrderedNode)));
  CurrentCodeBlock = nullptr;
}

void IREmitter::ReplaceAllUsesWithInclusive(OrderedNode *Node, OrderedNode *NewNode, IR::NodeWrapperIterator After, IR::NodeWrapperIterator End) {
  uintptr_t ListBegin = ListData.Begin();
  uintptr_t DataBegin = Data.Begin();

  while (After != End) {
    OrderedNodeWrapper *WrapperOp = After();
    OrderedNode *RealNode = WrapperOp->GetNode(ListBegin);
    FEXCore::IR::IROp_Header *IROp = RealNode->Op(DataBegin);

    uint8_t NumArgs = IR::GetArgs(IROp->Op);
    for (uint8_t i = 0; i < NumArgs; ++i) {
      if (IROp->Args[i].ID() == Node->Wrapped(ListBegin).ID()) {
        Node->RemoveUse();
        NewNode->AddUse();
        IROp->Args[i].NodeOffset = NewNode->Wrapped(ListBegin).NodeOffset;
      }
    }

    ++After;
  }
}

void IREmitter::ReplaceNodeArgument(OrderedNode *Node, uint8_t Arg, OrderedNode *NewArg) {
  uintptr_t ListBegin = ListData.Begin();
  uintptr_t DataBegin = Data.Begin();

  FEXCore::IR::IROp_Header *IROp = Node->Op(DataBegin);
  OrderedNodeWrapper OldArgWrapper = IROp->Args[Arg];
  OrderedNode *OldArg = OldArgWrapper.GetNode(ListBegin);
  OldArg->RemoveUse();
  NewArg->AddUse();
  IROp->Args[Arg].NodeOffset = NewArg->Wrapped(ListBegin).NodeOffset;
}

void IREmitter::RemoveArgUses(OrderedNode *Node) {
  uintptr_t ListBegin = ListData.Begin();
  uintptr_t DataBegin = Data.Begin();

  FEXCore::IR::IROp_Header *IROp = Node->Op(DataBegin);

  uint8_t NumArgs = IR::GetArgs(IROp->Op);
  for (uint8_t i = 0; i < NumArgs; ++i) {
    auto ArgNode = IROp->Args[i].GetNode(ListBegin);
    ArgNode->RemoveUse();
  }
}

void IREmitter::Remove(OrderedNode *Node) {
  RemoveArgUses(Node);

  Node->Unlink(ListData.Begin());
}

IREmitter::IRPair<IROp_CodeBlock> IREmitter::CreateNewCodeBlock() {
  auto OldCursor = GetWriteCursor();
  SetWriteCursor(CodeBlocks.back());

  auto CodeNode = CreateCodeNode();

  auto NewNode = _Dummy();
  SetCodeNodeBegin(CodeNode, NewNode);

  auto EndBlock = _EndBlock(0);
  SetCodeNodeLast(CodeNode, EndBlock);

  if (CurrentCodeBlock) {
    LinkCodeBlocks(CurrentCodeBlock, CodeNode);
  }

  SetWriteCursor(OldCursor);

  return CodeNode;
}

void IREmitter::SetCurrentCodeBlock(OrderedNode *Node) {
  CurrentCodeBlock = Node;
  LogMan::Throw::A(Node->Op(Data.Begin())->Op == OP_CODEBLOCK, "Node wasn't codeblock. It was '%s'", std::string(IR::GetName(Node->Op(Data.Begin())->Op)).c_str());
  SetWriteCursor(Node->Op(Data.Begin())->CW<IROp_CodeBlock>()->Begin.GetNode(ListData.Begin()));
}

}

