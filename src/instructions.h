#ifndef DIS_INSTRUCTIONS_H
#define DIS_INSTRUCTIONS_H

#include "execution.h"

// Operand sizes and types are given the last character in the instruction
// mnemonic, as follows:
//
// Character | Operand size and type
// --------- | ------------------------------
// W         | word, 32-bit two's complement
// B         | byte, 8-bit unsigned
// F         | float, 64-bit IEEE format
// L         | big, 64-bit two's complement
// P         | pointer
// C         | Unicode string encoded in UTF-8
// M         | memory
// MP        | memory containing pointers
//
// Two more operand types are defined to provide "short" types used by other
// Languages: signed 16-bit integers (short word) and 32-bit IEEE floating-point
// numbers (short real/float). Support for them is limited to conversion to and
// from words and reals/floats respectively. Their instructions are marked with
// an asterisk (*).

typedef enum Instruction {
    IN_NOP     = 0x00, // no operation
    IN_ALT     = 0x01, // alternate between communications
    IN_NBALT   = 0x02, // non-blocking alternate
    IN_GOTO    = 0x03, // comnputed goto
    IN_CALL    = 0x04, // call local function
    IN_FRAME   = 0x05, // allocate frame for local call
    IN_SPAWN   = 0x06, // spawn a new thread and call function
    IN_RUNT    = 0x07, // TODO unknown
    IN_LOAD    = 0x08, // load module
    IN_MCALL   = 0x09, // inter-module call
    IN_MSPAWN  = 0x0A, // module spawn function
    IN_MFRAME  = 0x0B, // allocate inter-module frame
    IN_RET     = 0x0C, // return from function
    IN_JMP     = 0x0D, // branch always (jump to address)
    IN_CASE    = 0x0E, // case compare integer and branch
    IN_EXIT    = 0x0F, // terminate thread
    IN_NEW     = 0x10, // allocate object
    IN_NEWA    = 0x11, // allocate array
    IN_NEWCB   = 0x12, // allocate channel (byte)
    IN_NEWCW   = 0x13, // allocate channel (word)
    IN_NEWCF   = 0x14, // allocate channel (real/float)
    IN_NEWCP   = 0x15, // allocate channel (pointer)
    IN_NEWCM   = 0x16, // allocate channel (memory)
    IN_NEWCMP  = 0x17, // allocate channel (memory containing pointers)
    IN_SEND    = 0x18, // send to channel
    IN_RECV    = 0x19, // receive from channel
    IN_CONSB   = 0x1A, // allocate new list element (byte)
    IN_CONSW   = 0x1B, // allocate new list element (word)
    IN_CONSP   = 0x1C, // allocate new list element (pointer)
    IN_CONSF   = 0x1D, // allocate new list element (real/float)
    IN_CONSM   = 0x1E, // allocate new list element (memory)
    IN_CONSMP  = 0x1F, // allocate new list element (memory containing pointers)

    IN_HEADB   = 0x20, // head of list (byte)
    IN_HEADW   = 0x21, // head of list (word)
    IN_HEADP   = 0x22, // head of list (pointer)
    IN_HEADF   = 0x23, // head of list (real/float)
    IN_HEADM   = 0x24, // head of list (memory)
    IN_HEADMP  = 0x25, // head of list (memory containing pointers)
    IN_TAIL    = 0x26, // tail of list
    IN_LEA     = 0x27, // load effective address
    IN_INDX    = 0x28, // array index
    IN_MOVP    = 0x29, // move pointer
    IN_MOVM    = 0x2A, // move memory
    IN_MOVMP   = 0x2B, // move memory and update reference counts
    IN_MOVB    = 0x2C, // move scalar (byte)
    IN_MOVW    = 0x2D, // move scalar (word)
    IN_MOVF    = 0x2E, // move scalar (real/float)
    IN_CVTBW   = 0x2F, // convert byte to word
    IN_CVTWB   = 0x30, // convert word to byte
    IN_CVTFW   = 0x31, // convert real/float to word
    IN_CVTWF   = 0x32, // convert word to real/float
    IN_CVTCA   = 0x33, // convert string to byte array
    IN_CVTAC   = 0x34, // convert byte array to string
    IN_CVTWC   = 0x35, // convert word to string
    IN_CVTCW   = 0x36, // convert string to word
    IN_CVTFC   = 0x37, // convert real/float to string
    IN_CVTCF   = 0x38, // convert string to real/float
    IN_ADDB    = 0x39, // add (byte)
    IN_ADDW    = 0x3A, // add (word)
    IN_ADDF    = 0x3B, // add (real/float)
    IN_SUBB    = 0x3C, // subtract (byte)
    IN_SUBW    = 0x3D, // subtract (word)
    IN_SUBF    = 0x3E, // subtract (real/float)
    IN_MULB    = 0x3F, // multiply (byte)

    IN_MULW    = 0x40, // multiply (word)
    IN_MULF    = 0x41, // multiply (real/float)
    IN_DIVB    = 0x42, // divide (byte)
    IN_DIVW    = 0x43, // divide (word)
    IN_DIVF    = 0x44, // divide (real/float)
    IN_MODW    = 0x45, // modulus (word)
    IN_MODB    = 0x46, // modulus (byte)
    IN_ANDB    = 0x47, // logical AND (byte)
    IN_ANDW    = 0x48, // logical AND (word)
    IN_ORB     = 0x49, // logical OR (byte)
    IN_ORW     = 0x4A, // logical OR (word)
    IN_XORB    = 0x4B, // exclusive OR (byte)
    IN_XORW    = 0x4C, // exclusive OR (word)
    IN_SHLB    = 0x4D, // shift left arithmetic (byte)
    IN_SHLW    = 0x4E, // shift left arithmetic (word)
    IN_SHRB    = 0x4F, // shift right arithmetic (byte)
    IN_SHRW    = 0x50, // shift right arithmetic (word)
    IN_INSC    = 0x51, // insert character into string
    IN_INDC    = 0x52, // index by character
    IN_ADDC    = 0x53, // add strings
    IN_LENC    = 0x54, // length of string
    IN_LENA    = 0x55, // length of array
    IN_LENL    = 0x56, // length of list
    IN_BEQB    = 0x57, // branch if equal (byte)
    IN_BNEB    = 0x58, // branch if not equal (byte)
    IN_BLTB    = 0x59, // branch if less than (byte)
    IN_BLEB    = 0x5A, // branch if less than or equal (byte)
    IN_BGTB    = 0x5B, // branch if greater than (byte)
    IN_BGEB    = 0x5C, // branch if greater than or equal (byte)
    IN_BEQW    = 0x5D, // branch if equal (word)
    IN_BNEW    = 0x5E, // branch if not equal (word)
    IN_BLTW    = 0x5F, // branch if less than (word)

    IN_BLEW    = 0x60, // branch if less than or equal (word)
    IN_BGTW    = 0x61, // branch if greater than (word)
    IN_BGEW    = 0x62, // branch if greater than or equal (word)
    IN_BEQF    = 0x63, // branch if equal (real/float)
    IN_BNEF    = 0x64, // branch if not equal (real/float)
    IN_BLTF    = 0x65, // branch if less than (real/float)
    IN_BLEF    = 0x66, // branch if less than or equal (real/float)
    IN_BGTF    = 0x67, // branch if greater than (real/float)
    IN_BGEF    = 0x68, // branch if greater than or equal (real/float)
    IN_BEQC    = 0x69, // branch if equal (string)
    IN_BNEC    = 0x6A, // branch if not equal (string)
    IN_BLTC    = 0x6B, // branch if less than (string)
    IN_BLEC    = 0x6C, // branch if less than or equal (string)
    IN_BGTC    = 0x6D, // branch if greater than (string)
    IN_BGEC    = 0x6E, // branch if greater than or equal (string)
    IN_SLICEA  = 0x6F, // slice array
    IN_SLICELA = 0x70, // assign to array slice
    IN_SLICEC  = 0x71, // slice string
    IN_INDW    = 0x72, // index by word
    IN_INDF    = 0x73, // index by real/float
    IN_INDB    = 0x74, // index by byte
    IN_NEGF    = 0x75, // negate real/float
    IN_MOVL    = 0x76, // move scalar (big/long)
    IN_ADDL    = 0x77, // add (big/long)
    IN_SUBL    = 0x78, // subtract (big/long)
    IN_DIVL    = 0x79, // divide (big/long)
    IN_MODL    = 0x7A, // modulus (big/long)
    IN_MULL    = 0x7B, // multiply (big/long)
    IN_ANDL    = 0x7C, // logical AND (big/long)
    IN_ORL     = 0x7D, // logical OR (big/long)
    IN_XORL    = 0x7E, // exclusive OR (big/long)
    IN_SHLL    = 0x7F, // shift left arithmetic (big/long)

    IN_SHRL    = 0x80, // shift right arithmetic (big/long)
    IN_BNEL    = 0x81, // branch if not equal (big/long)
    IN_BLTL    = 0x82, // branch if less than (big/long)
    IN_BLEL    = 0x83, // branch if less than or equal (big/long)
    IN_BGTL    = 0x84, // branch if greater than (big/long)
    IN_BGEL    = 0x85, // branch if greater than or equal (big/long)
    IN_BEQL    = 0x86, // branch if equal (big/long)
    IN_CVTLF   = 0x87, // convert big/long to real/float
    IN_CVTFL   = 0x88, // convert real/float to big/long
    IN_CVTLW   = 0x89, // convert big/long to word
    IN_CVTWL   = 0x8A, // convert word to big/long
    IN_CVTLC   = 0x8B, // convert big/long to string
    IN_CVTCL   = 0x8C, // convert string to big/long
    IN_HEADL   = 0x8D, // head of list (big/long)
    IN_CONSL   = 0x8E, // allocate new list element (big/long)
    IN_NEWCL   = 0x8F, // allocate channel (big/long)
    IN_CASEC   = 0x90, // case compare string and branch
    IN_INDL    = 0x91, // index by big/long
    IN_MOVPC   = 0x92, // move program counter
    IN_TCMP    = 0x93, // compare types
    IN_MNEWZ   = 0x94, // allocate object
    IN_CVTRF   = 0x95, // convert short real/float to real/float*
    IN_CVTFR   = 0x96, // convert real/float* to short real/float*
    IN_CVTWS   = 0x97, // convert word to short word*
    IN_CVTSW   = 0x98, // convert short word to word*
    IN_LSRW    = 0x99, // logical shift right (word)
    IN_LSRL    = 0x9A, // logical shift right (long)
    IN_ECLR    = 0x9B, // TODO unknown
    IN_NEWZ    = 0x9C, // allocate object, zero fill non-pointers
    IN_NEWAZ   = 0x9D, // allocate array, zero fill non-pointers
} Instruction;

/// `alt` - Alternate between communications
///
/// The `alt` instruction selects between a set of channels ready to communicate.
/// The `src` argument is the address of a structure described in `Alt`.
///
///The vector is divided into two sections; the first lists the channels ready
/// to send values, the second lists channels either ready to receive or an
/// array of channels each of which may be ready to receive. The counts of the
/// sender and receiver channels are stored as the first and second words
/// addressed by `src`. An `alt` instruction proceeds by testing each channel
/// for readiness to communicate. A ready channel is added to a list. If the
/// list is empty after each channel has been considered, the thread blocks at
/// the `alt` instruction waiting for a channel to become ready; otherwise, a
/// channel is picked at random from the ready set.
///
///The `alt` instruction then uses the selected channel to perform the
/// communication using the `val` address as either a source for send or a
/// destination for receive. The numeric index of the selected vector element
/// is placed in `dst`.
///
/// \param context The execution context.
/// \param src Address to a collection of channels to select from.
/// \param ptr The numeric index of the selected channel.
void alt(ExecutionContext *context, Alt *src, uptr *ptr);

/// `nbalt` - Non blocking alternate
///
/// The `nbalt` instruction has the same operands and function as `alt()`, except
/// that if no channel is ready to communicate, the instruction does not block.
/// When no channels are ready, control is transferred to the PC in the last
/// element of the table addressed by `dst`.
///
/// \param context The execution context.
/// \param src Address to a collection of channels to select from.
/// \param ptr The numeric index of the selected channel.
void nbalt(ExecutionContext *context, Alt *src, uptr *ptr);

/// `goto` - Computed goto
///
/// The `goto` instruction performs a computed goto. The `src` operand must be
/// an integer index into a table of PC values specified by the `dst` operand.
///
/// \param context The execution context.
/// \param src An integer index into a table of program counter values provided
/// by `dst`.
/// \param dst A table of program counter values.
void goto_(ExecutionContext *context, uptr src, uptr *dst);

/// `call` - Call local function
///
/// The `call` instruction performs a function call to a routine in the same
/// module. The `src` argument specifies a frame created by `new()`. The
/// current value of `pc` is stored in link(src), the current value of `fp` is
/// stored in frame(src) and the module link register is set to 0. The value of
/// `fp` is then set to `src` and control is transferred to the program counter
/// specified by `dst`.
///
/// \param context The execution context.
/// \param src A frame created by `\ref new` to use for the called routine.
/// \param dst The program counter to transfer control to.
void call(ExecutionContext *context, Frame *src, uptr *dst);

/// `frame` - Allocate frame for local call
///
/// The `frame` instruction creates a new stack frame for a call to a function
/// in the same module. The frame is initialized according to the type
/// descriptor supplied as the `src1` operand. A pointer to the newly created
/// frame is stored in the `src2` operand.
///
/// \param context The execution context.
/// \param src1 Type descriptor to initialse the frame with.
/// \param src2 Location to store the newly created frame in.
void frame(ExecutionContext *context, TypeDescriptor src1, Frame *src2);

/// `spawn` - Spawn function
///
/// The `spawn` instruction creates a new thread and calls the function
/// specified by the `dst` operand. The argument frame passed to the thread
/// function is specified by the `src` operand and should have been created by
/// the `\ref frame` instruction.
///
/// \param context The execution context.
/// \param src The frame to use for the new function.
/// \param dst The program counter to transfer control to in the new thread.
void spawn(ExecutionContext *context, Frame *src, uptr *dst);

/// UNKNOWN
void runt(ExecutionContext *context);

/// `load` - Load module
///
/// The `load` instruction loads a new module into the heap. The module might
/// optionally be compiled into machine code depending on the module header.
/// The `src1` operand is a pathname to the file containing the object code for
/// the module. The `src2` operand specifies the address of a linkage descriptor
/// for the module (see below). A reference to the newly loaded module is stored
/// in the `dst` operand. If the module could not be loaded for any reason, then
/// dst will be set to `H`.
///
/// The linkage descriptor referenced by the `src2` operand is a table in data
/// space that lists the functions imported by the current module from the
/// module to be loaded. It is described in `LinkageDescriptor`. For each entry,
/// `load` checks that a function with the same name in the newly loaded
/// module exists, with the same signature. Otherwise, the load will fail and
/// `dst` will be set to `H`.
///
/// The entries in the linkage descriptor form an array of linkage records
/// (internal to the virtual machine) associated with the module pointer
/// returned in `dst`, that is indexed by operators `mframe()`, `mcall()`
/// and `mspawn()` to refer to functions in that module. The linkage scheme
/// provides a level of indirection that allows a module to be loaded using any
/// module declaration that is a valid subset of the implementation module’s
/// declaration, and allows entry points to be added to modules without
/// invalidating calling modules.
///
/// \param context The execution context.
/// \param src1 Pathname to the file containinbg object code for the module.
/// \param src2 Address of a linkage descriptor for the module.
/// \param dst Location to store a reference to the newly-loaded module.
void load(ExecutionContext *context, char *src1, LinkageDescriptor *src2,
          Module *dst);

/// `mcall` - Inter-module call
///
/// The `mcall` instruction calls a function in another module. The first
/// argument specifies a new frame for the called procedure and must have been
/// built using the `mframe()` instruction. The `src3` operand is a module
/// reference generated by a successful `load()` instruction. The `src2` operand
/// specifies the index for the called function in the array of linkage records
/// associated with that module reference (see the load instruction).
///
/// \param context The execution context.
/// \param src1 The frame to use for the new function.
/// \param src2 The index of the called function in the array of linkage records.
/// \param src3 The module reference generated by `load()`.
void mcall(ExecutionContext *context, Frame *src1, uptr src2, Module *src3);

/// `mspawn` - Module spawn function
///
/// The `mspawn` instruction creates a new thread, which starts executing a
/// function in another module. The first argument specifies a new frame for the
/// called procedure and must have been built using the `mframe()` instruction.
/// The `src3` operand is a module reference generated by a successful `load()`
/// instruction. The `src2` operand specifies the index for the called function
/// in the array of linkage records associated with that module reference
/// (see the `load()` instruction).
/// \param context The execution context.
/// \param src1 The frame to use for the new function.
/// \param src2 The index of the called function in the array of linkage records.
/// \param src3 The module reference generated by `load()`.
void mspawn(ExecutionContext *context, Frame *src1, uptr src2, Module *src3);

/// `mframe` - Allocate inter-module frame
///
/// The `mframe` instruction allocates a new frame for a procedure call into
/// another module. The `src1` operand specifies the location of a module
/// pointer created as the result of a successful `load()` instruction. The
/// `src2` operand specifies the index for the called function in the array of
/// linkage records associated with that module pointer (see the `load()`
/// instruction). A pointer to the initialized frame is stored in `dst`. The
/// `src2` operand specifies the linkage number of the function to be called in
/// the module specified by `src1`.
/// \param context
/// \param src1
/// \param src2
/// \param dst
void mframe(ExecutionContext *context, Module *src1, uptr src2, Frame *dst);
void ret(ExecutionContext *context);
void jmp(ExecutionContext *context);
void case_(ExecutionContext *context);
void exit_(ExecutionContext *context);
void new_(ExecutionContext *context);
void newa(ExecutionContext *context);
void newcv(ExecutionContext *context);
void newcf(ExecutionContext *context);
void newcp(ExecutionContext *context);
void newcm(ExecutionContext *context);
void newcmp(ExecutionContext *context);
void send(ExecutionContext *context);
void recv(ExecutionContext *context);
void consb(ExecutionContext *context);
void consw(ExecutionContext *context);
void consp(ExecutionContext *context);
void consf(ExecutionContext *context);
void consm(ExecutionContext *context);
void consmp(ExecutionContext *context);

void headb(ExecutionContext *context);
void headw(ExecutionContext *context);
void headp(ExecutionContext *context);
void headf(ExecutionContext *context);
void headm(ExecutionContext *context);
void headmp(ExecutionContext *context);
void tail(ExecutionContext *context);
void lea(ExecutionContext *context);
void indx(ExecutionContext *context);
void movp(ExecutionContext *context);
void movm(ExecutionContext *context);
void movmp(ExecutionContext *context);
void movb(ExecutionContext *context);
void movw(ExecutionContext *context);
void movf(ExecutionContext *context);
void cvtbw(ExecutionContext *context);
void cvtwb(ExecutionContext *context);
void cvtfw(ExecutionContext *context);
void cvtwf(ExecutionContext *context);
void cvtca(ExecutionContext *context);
void cvtac(ExecutionContext *context);
void cvtwc(ExecutionContext *context);
void cvtcw(ExecutionContext *context);
void cvtfc(ExecutionContext *context);
void cvtcf(ExecutionContext *context);
void addb(ExecutionContext *context);
void addw(ExecutionContext *context);
void addf(ExecutionContext *context);
void subb(ExecutionContext *context);
void subf(ExecutionContext *context);
void mulb(ExecutionContext *context);

void mulw(ExecutionContext *context);
void mulf(ExecutionContext *context);
void divb(ExecutionContext *context);
void divw(ExecutionContext *context);
void divf(ExecutionContext *context);
void modw(ExecutionContext *context);
void modb(ExecutionContext *context);
void andb(ExecutionContext *context);
void andw(ExecutionContext *context);
void orb(ExecutionContext *context);
void orw(ExecutionContext *context);
void xorb(ExecutionContext *context);
void xorw(ExecutionContext *context);
void shlb(ExecutionContext *context);
void shlw(ExecutionContext *context);
void shrb(ExecutionContext *context);
void shrw(ExecutionContext *context);
void insc(ExecutionContext *context);
void indc(ExecutionContext *context);
void addc(ExecutionContext *context);
void lenc(ExecutionContext *context);
void lena(ExecutionContext *context);
void lenl(ExecutionContext *context);
void beqb(ExecutionContext *context);
void bneb(ExecutionContext *context);
void bltb(ExecutionContext *context);
void bleb(ExecutionContext *context);
void bgtb(ExecutionContext *context);
void bgeb(ExecutionContext *context);
void beqw(ExecutionContext *context);
void bnew(ExecutionContext *context);
void bltw(ExecutionContext *context);

void blew(ExecutionContext *context);
void bgtw(ExecutionContext *context);
void bgew(ExecutionContext *context);
void beqf(ExecutionContext *context);
void bnef(ExecutionContext *context);
void bltf(ExecutionContext *context);
void bgtf(ExecutionContext *context);
void bgef(ExecutionContext *context);
void beqc(ExecutionContext *context);
void bnec(ExecutionContext *context);
void bltc(ExecutionContext *context);
void blec(ExecutionContext *context);
void bgtc(ExecutionContext *context);
void bgec(ExecutionContext *context);
void slicea(ExecutionContext *context);
void slicela(ExecutionContext *context);
void slicec(ExecutionContext *context);
void indw(ExecutionContext *context);
void indf(ExecutionContext *context);
void indb(ExecutionContext *context);
void negf(ExecutionContext *context);
void movl(ExecutionContext *context);
void addl(ExecutionContext *context);
void subl(ExecutionContext *context);
void divl(ExecutionContext *context);
void mull(ExecutionContext *context);
void andl(ExecutionContext *context);
void orl(ExecutionContext *context);
void xorl(ExecutionContext *context);
void shll(ExecutionContext *context);

void shrl(ExecutionContext *context);
void bnel(ExecutionContext *context);
void bltl(ExecutionContext *context);
void blel(ExecutionContext *context);
void bgtl(ExecutionContext *context);
void bgel(ExecutionContext *context);
void beql(ExecutionContext *context);
void cvtlf(ExecutionContext *context);
void cvtfl(ExecutionContext *context);
void cvtlw(ExecutionContext *context);
void cvtwl(ExecutionContext *context);
void cvtlc(ExecutionContext *context);
void cvtcl(ExecutionContext *context);
void headl(ExecutionContext *context);
void consl(ExecutionContext *context);
void newcl(ExecutionContext *context);
void casec(ExecutionContext *context);
void indl(ExecutionContext *context);
void movpc(ExecutionContext *context);
void tcmp(ExecutionContext *context);
void mnewz(ExecutionContext *context);
void cvtrf(ExecutionContext *context);
void cvtfr(ExecutionContext *context);
void cvtws(ExecutionContext *context);
void cvtsw(ExecutionContext *context);
void lsrw(ExecutionContext *context);
void lsrl(ExecutionContext *context);
void eclr(ExecutionContext *context);
void newz(ExecutionContext *context);
void newaz(ExecutionContext *context);

#endif //DIS_INSTRUCTIONS_H
