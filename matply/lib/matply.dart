library matply;

export 'src/core.dart' show
  /// core-global-setting
  getInstances,
  initMp,
  freeMp,
  set_visible_round,
  get_visible_round,
  set_round,
  get_round,
  set_seed,
  set_max_thread_support,
  get_max_thread_support,
  get_max_thread_sys,
  set_simple_dvcst_value,
  get_simple_dvcst_value,
  set_complex_dvcst_value,
  get_complex_dvcst_value,
  get_time,
  set_multp_shown,
  get_multp_shown,
  set_simple_dvcst_value_force,
  set_complex_dvcst_value_force,
  Alert,
  Since,
  defaultSpc,
  pubCacheDir,
  dylib,
  SpecialAttributes,
  Matrix,
  Point2D,
  MultiDatas2,
  MultiDatas3,
  MultiDatas4,
  VERSION,
  /// list extension
  ListExtensions,
  TwoDimListExtensions,
  ShapeRangeError,
  /// test
  TestOneArrayPointer,
  TestArrayPointer,
  oneListToArray,
  oneListToArrayInt32,
  justTestOmp,
  MatrixType,
  freeOp,
  freeTp,
  allocateOp,
  /// C constants
  Pi,
  e,
  inf,
  negativeinf,
  nan,
  euler,
  /// Basement methods
  BasementMethods,
  /// Linear Algebra
  Linalg,
  /// Pure math
  Point2DOperator,
  diffCentral,
  getCartesianProduct,
  PureMath,
  GeometryGenerator,
  /// Probability Theory and Statistics
  RandomExtension,
  ProbStat,
  /// Abstract Visualization
  Visualization,
  /// Functional tools
  Functools,
  /// Cpp Extension
  MatplyTypeCppExtension
;

export 'src/data_frame/data_frame.dart' show Dataframe;
export 'src/data_frame/series.dart' show Series;
export 'src/io/csv.dart' show CSVReader, CSV;