#pragma once

#include <vector>
#include <string>
#include <map>
#include <opencv2/opencv.hpp>


// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------
typedef float track_t;
typedef cv::Point_<track_t> Point_t;
#define Mat_t CV_32FC

///
/// \brief config_t
///
typedef std::map<std::string, std::string> config_t;

///
/// \brief The CRegion class
///
class CRegion
{
public:
    CRegion()
        : m_type(""), m_confidence(-1)
    {
    }

    CRegion(const cv::Rect& rect)
        : m_brect(rect)
    {
        B2RRect();
    }

    CRegion(const cv::RotatedRect& rrect)
        : m_rrect(rrect)
    {
        R2BRect();
    }

    CRegion(const cv::Rect& rect, const std::string& type, float confidence)
        : m_brect(rect), m_type(type), m_confidence(confidence)
    {
        B2RRect();
    }

    cv::RotatedRect m_rrect;
    cv::Rect m_brect;

    std::string m_type;
    float m_confidence = -1;

private:
    ///
    /// \brief R2BRect
    /// \return
    ///
    cv::Rect R2BRect()
    {
        m_brect = m_rrect.boundingRect();
        return m_brect;
    }
    ///
    /// \brief B2RRect
    /// \return
    ///
    cv::RotatedRect B2RRect()
    {
        m_rrect = cv::RotatedRect(m_brect.tl(), cv::Point2f(static_cast<float>(m_brect.x + m_brect.width), static_cast<float>(m_brect.y)), m_brect.br());
        return m_rrect;
    }
};

typedef std::vector<CRegion> regions_t;

///
///
///
namespace tracking
{
///
/// \brief The Detectors enum
///
enum Detectors
{
    Motion_VIBE,
    Motion_MOG,
    Motion_GMG,
    Motion_CNT,
    Motion_SuBSENSE,
    Motion_LOBSTER,
    Motion_MOG2,
    Face_HAAR,
    Pedestrian_HOG,
    Pedestrian_C4,
    SSD_MobileNet,
    Yolo_OCV,
	Yolo_Darknet
};

///
/// \brief The DistType enum
///
enum DistType
{
    DistCenters = 0,
    DistRects = 1,
    DistJaccard = 2
};

///
/// \brief The FilterGoal enum
///
enum FilterGoal
{
    FilterCenter = 0,
    FilterRect = 1
};

///
/// \brief The KalmanType enum
///
enum KalmanType
{
    KalmanLinear = 0,
    KalmanUnscented = 1,
    KalmanAugmentedUnscented
};

///
/// \brief The MatchType enum
///
enum MatchType
{
    MatchHungrian = 0,
    MatchBipart = 1
};

///
/// \brief The LostTrackType enum
///
enum LostTrackType
{
    TrackNone = 0,
    TrackKCF = 1,
    TrackMIL,
    TrackMedianFlow,
    TrackGOTURN,
    TrackMOSSE,
    TrackCSRT,
    TrackDAT,
    TrackSTAPLE
};
}