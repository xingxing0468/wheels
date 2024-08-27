from optparse import OptionParser
import os


if __name__ == '__main__':
    parser = OptionParser()
    parser.add_option("--libs", dest="libs", type=str,
                  help="libs to link", default="/tmp/tmp")
    options,_ = parser.parse_args()
    libs = options.libs.split(',')
    for l in libs:
        print("ll: {}, path: {}".format(l, [os.path.dirname(os.path.abspath(lib)) for lib in libs]))