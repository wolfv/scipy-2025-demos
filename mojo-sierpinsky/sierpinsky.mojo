from gpu import thread_idx, block_idx, block_dim
from gpu.host import DeviceContext
from layout import LayoutTensor, Layout

alias SIZE = 30
alias LAYOUT = Layout.row_major(SIZE, SIZE)
alias BLOCKS_PER_GRID = (4, 4)
alias THREADS_PER_BLOCK = (16, 16)
alias dtype = DType.uint8

fn sierpinsky[layout: Layout, size: Int](img: LayoutTensor[mut=True, dtype, layout]):
    x = thread_idx.x + block_dim.x * block_idx.x
    y = thread_idx.y + block_dim.y * block_idx.y
    if x >= size or y >= size: return
    if (x & y) == 0:
        img[x, y] = 255


def main():
    ctx = DeviceContext()
    img_buf = ctx.enqueue_create_buffer[dtype](SIZE * SIZE).enqueue_fill(0)
    # device tensor
    img = LayoutTensor[mut=True, dtype, LAYOUT](img_buf.unsafe_ptr())
    ctx.enqueue_function[sierpinsky[LAYOUT, SIZE]](img, grid_dim=BLOCKS_PER_GRID, block_dim=THREADS_PER_BLOCK)
    ctx.synchronize()

    with img_buf.map_to_host() as img_host:
        # host tensor
        img_ = LayoutTensor[mut=False, dtype, LAYOUT](img_host.unsafe_ptr())
        for i in range(SIZE):
            for j in range(SIZE):
                if img_[i, j] == 255:
                    print("*", end="")
                else:
                    print(" ", end="")
            print()
