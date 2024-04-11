import sys, os, io, math
import typing
from PIL import Image

BLOCK_SIZE = 512

CanResult = tuple[bytes, int] # bytes to add, block count

def can_png(file: typing.TextIO) -> CanResult:
    bytes_ = bytes()
    image_file = Image.open(file)
    width, height = image_file.size
    bytes_ += width.to_bytes(4, "little")
    bytes_ += height.to_bytes(4, "little")

    pixels = image_file.load()
    for y in range(height):
        for x in range(width):
            r, g, b, a = pixels[x, y]
            bytes_ += r.to_bytes(1, "little")
            bytes_ += g.to_bytes(1, "little")
            bytes_ += b.to_bytes(1, "little")
            bytes_ += a.to_bytes(1, "little")
    return bytes_
            
def can_text(file: typing.TextIO) -> CanResult:
    text = file.read()
    text_bytes = text
    return text_bytes + b'\0'

CANNERS: dict[str, typing.Callable[[typing.TextIO], CanResult]] = {
    ".png": can_png,
    ".frag": can_text,
    ".vert": can_text,
}

def can(dir, file: typing.BinaryIO):
    # Magic
    file.write(b'CAN!')

    index: dict[str, tuple[int, int, bytes, int]] = {}
    bytes_count = 0
    for (dirpath, _, filenames) in os.walk(dir):
        for src_file_name in filenames:
            src_file = open(os.path.join(dirpath, src_file_name), "rb")
            root, ext = os.path.splitext(src_file_name)
            if ext in CANNERS.keys():
                print("Canning {}...".format(src_file_name))
                bytes_ = CANNERS[ext](src_file)
                length = len(bytes_)

                if length == 0:
                    print("\tWARNING: No bytes generated for this asset!")

                index[src_file_name] = (bytes_, bytes_count, length)
                bytes_count += length

    written_count = len(b'CAN!')

    # write index
    file.write(len(index).to_bytes(4, "little"))
    written_count += 4
    for entry_name in index.keys():
        _, bytes_start, bytes_length = index[entry_name]
        file.write(entry_name.encode("utf-8"))
        file.write(b'\0')
        file.write(bytes_start.to_bytes(4, "little"))
        file.write(bytes_length.to_bytes(4, "little"))

        written_count += 8 + len(b'\0') + len(entry_name.encode("utf-8"))

    # write data
    data_length = 0
    print("Data begins in CAN file @ {} bytes".format(written_count))
    for entry_name in index.keys():
        bytes_, bytes_start, byte_length = index[entry_name]

        print("{} (@{}): {}, {}".format(entry_name, written_count, bytes_start, byte_length))
        file.write(bytes_)

        data_length += byte_length
        written_count += len(bytes_)
    
    print("Wrote {} bytes total, data section {} bytes".format(written_count, data_length))


class canner_colors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKCYAN = '\033[96m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'


def main():
    print("""
       _              _                                         _ 
      (_)            | |                                       | |
__   _____   ____ _  | | __ _    ___ __ _ _ __  _ __   ___ _ __| |
\ \ / / \ \ / / _` | | |/ _` |  / __/ _` | '_ \| '_ \ / _ \ '__| |
 \ V /| |\ V / (_| | | | (_| | | (_| (_| | | | | | | |  __/ |  |_|
  \_/ |_| \_/ \__,_| |_|\__,_|  \___\__,_|_| |_|_| |_|\___|_|  (_)
                                canner.py by Angus Goucher (@gusg21)
          """)

    if len(sys.argv) < 3:
        print("Incorrect arguments! canner.py [input dir] [output dir]")
        return

    src_dir = sys.argv[1]
    dst_file = sys.argv[2]

    print("Canning from {} to {}...".format(src_dir, dst_file))

    can_file: io.TextIOWrapper
    try:
        can_file = open(dst_file, "wb+")
    except OSError:
        print("Failed to create file {}!".format(dst_file))
        return
    
    can(src_dir, can_file)

    print("All done!")

if __name__ == "__main__":
    main()