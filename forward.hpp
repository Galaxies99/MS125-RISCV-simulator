# include "execution.hpp"
# include "memoryaccess.hpp"
# include "instructiondecode.hpp"

# ifndef _FORWARD_
  # define _FORWARD_
  
void Forward(Execution &EX, InstructionDecode &ID) {
  switch(EX.inst.type) {
    case LUI:
    case AUIPC:
    case JAL:
    case JALR:
    case ADDI:
    case SLTI:
    case SLTIU:
    case ANDI:
    case ORI:
    case XORI:
    case SLLI:
    case SRLI:
    case SRAI:
    case ADD:
    case SUB:
    case SLL:
    case SLT:
    case SLTU:
    case XOR:
    case SRL:
    case SRA:
    case OR:
    case AND:
      if(ID.inst.rs1 == EX.inst.rd && ID.inst.rs1 != 0)
        ID.inst.src1 = EX.inst.result;
      if(ID.inst.rs2 == EX.inst.rd && ID.inst.rs2 != 0)
        ID.inst.src2 = EX.inst.result;
      break;
    default: break;
  }
}
  
void Forward(MemoryAccess &MA, InstructionDecode &ID) {
  switch(MA.inst.type) {
    case LUI:
    case AUIPC:
    case JAL:
    case JALR:
    case LB:
    case LW:
    case LH:
    case LBU:
    case LHU:
    case ADDI:
    case SLTI:
    case SLTIU:
    case ANDI:
    case ORI:
    case XORI:
    case SLLI:
    case SRLI:
    case SRAI:
    case ADD:
    case SUB:
    case SLL:
    case SLT:
    case SLTU:
    case XOR:
    case SRL:
    case SRA:
    case OR:
    case AND:
      if(ID.inst.rs1 == MA.inst.rd && ID.inst.rs1 != 0)
        ID.inst.src1 = MA.inst.result;
      if(ID.inst.rs2 == MA.inst.rd && ID.inst.rs2 != 0)
        ID.inst.src2 = MA.inst.result;
      break;
    default: break;
  }
}

void Forward(MemoryAccess &MA, Execution &EX) {
  switch(MA.inst.type) {
    case LUI:
    case AUIPC:
    case JAL:
    case JALR:
    case LB:
    case LW:
    case LH:
    case LBU:
    case LHU:
    case ADDI:
    case SLTI:
    case SLTIU:
    case ANDI:
    case ORI:
    case XORI:
    case SLLI:
    case SRLI:
    case SRAI:
    case ADD:
    case SUB:
    case SLL:
    case SLT:
    case SLTU:
    case XOR:
    case SRL:
    case SRA:
    case OR:
    case AND:
      if(EX.inst.rs1 == MA.inst.rd && EX.inst.rs1 != 0)
        EX.inst.src1 = MA.inst.result;
      if(EX.inst.rs2 == MA.inst.rd && EX.inst.rs2 != 0)
        EX.inst.src2 = MA.inst.result;
      break;
    default: break;
  }
}
  
# endif
