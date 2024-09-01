import unittest

if __name__ == "__main__":
    # Discover and run all tests
    test_suite = unittest.TestLoader().discover(".")
    result = unittest.TextTestRunner(verbosity=2).run(test_suite)
    exit(not result.wasSuccessful())
