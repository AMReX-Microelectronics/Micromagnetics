//Algorithm to calculate Laplacian for exchange term in LLG equation

/**
 * Perform derivative along x on a nodal grid, from a cell-centered field `F`*/
AMREX_GPU_HOST_DEVICE AMREX_FORCE_INLINE
static amrex::Real UpwardDx (
    amrex::Array4<amrex::Real> const& F,
    int const i, int const j, int const k, const Geometry& geom) {

    // extract dx from the geometry object
    GpuArray<Real,AMREX_SPACEDIM> dx = geom.CellSizeArray();

    amrex::Real const inv_dx = 1./dx[0];
    return inv_dx*( F(i+1,j,k) - F(i,j,k) );
}


/**
 * Perform derivative along x on a nodal grid, from a cell-centered field `F`*/
AMREX_GPU_HOST_DEVICE AMREX_FORCE_INLINE
static amrex::Real DownwardDx (
    amrex::Array4<amrex::Real> const& F,
    int const i, int const j, int const k, const Geometry& geom) {

    // extract dx from the geometry object
    GpuArray<Real,AMREX_SPACEDIM> dx = geom.CellSizeArray();

    amrex::Real const inv_dx = 1./dx[0];
    return inv_dx*( F(i,j,k) - F(i-1,j,k) );
}


/**
 * Perform derivative along y on a nodal grid, from a cell-centered field `F`*/
AMREX_GPU_HOST_DEVICE AMREX_FORCE_INLINE
static amrex::Real UpwardDy (
    amrex::Array4<amrex::Real> const& F,
    int const i, int const j, int const k, const Geometry& geom) {

    // extract dx from the geometry object
    GpuArray<Real,AMREX_SPACEDIM> dx = geom.CellSizeArray();

    amrex::Real const inv_dy = 1./dx[1];
    return inv_dy*( F(i,j+1,k) - F(i,j,k) );
}


/**
 * Perform derivative along y on a nodal grid, from a cell-centered field `F`*/
AMREX_GPU_HOST_DEVICE AMREX_FORCE_INLINE
static amrex::Real DownwardDy (
    amrex::Array4<amrex::Real> const& F,
    int const i, int const j, int const k, const Geometry& geom) {

    // extract dx from the geometry object
    GpuArray<Real,AMREX_SPACEDIM> dx = geom.CellSizeArray();

    amrex::Real const inv_dy = 1./dx[1];
    return inv_dy*( F(i,j,k) - F(i,j-1,k) );
}



/**
 * Perform derivative along z on a nodal grid, from a cell-centered field `F`*/
AMREX_GPU_HOST_DEVICE AMREX_FORCE_INLINE
static amrex::Real UpwardDz (
    amrex::Array4<amrex::Real> const& F,
    int const i, int const j, int const k, const Geometry& geom) {

    // extract dx from the geometry object
    GpuArray<Real,AMREX_SPACEDIM> dx = geom.CellSizeArray();

    amrex::Real const inv_dz = 1./dx[2];
    return inv_dz*( F(i,j,k+1) - F(i,j,k) );
}


/**
 * Perform derivative along z on a nodal grid, from a cell-centered field `F`*/
AMREX_GPU_HOST_DEVICE AMREX_FORCE_INLINE
static amrex::Real DownwardDz (
    amrex::Array4<amrex::Real> const& F,
    int const i, int const j, int const k, const Geometry& geom) {

    // extract dx from the geometry object
    GpuArray<Real,AMREX_SPACEDIM> dx = geom.CellSizeArray();

    amrex::Real const inv_dz = 1./dx[2];
    return inv_dz*( F(i,j,k) - F(i,j,k-1) );
}

/**
  * Perform divergence of gradient along x on M field */
 AMREX_GPU_HOST_DEVICE AMREX_FORCE_INLINE
 static amrex::Real LaplacianDx_Mag (
    amrex::Array4<amrex::Real> const& F,
    amrex::Real const Ms_lo_x, amrex::Real const Ms_hi_x,
    int const i, int const j, int const k, const Geometry& geom) {

    // extract dx from the geometry object
    GpuArray<Real,AMREX_SPACEDIM> dx = geom.CellSizeArray();

    amrex::Real const inv_dx = 1./dx[0];
    if (Ms_hi_x == 0.){
        return inv_dx*(0. - DownwardDx(F, i, j, k, geom));
    } else if (Ms_lo_x == 0.){
        return inv_dx*(UpwardDx(F, i, j, k, geom) - 0.);
    } else {
        return inv_dx*(UpwardDx(F, i, j, k, geom) - DownwardDx(F, i, j, k, geom));
    }
 }


/**
  * Perform divergence of gradient along y on M field */
 AMREX_GPU_HOST_DEVICE AMREX_FORCE_INLINE
 static amrex::Real LaplacianDy_Mag (
    amrex::Array4<amrex::Real> const& F,
    amrex::Real const Ms_lo_y, amrex::Real const Ms_hi_y,
    int const i, int const j, int const k, const Geometry& geom) {

    // extract dx from the geometry object
    GpuArray<Real,AMREX_SPACEDIM> dx = geom.CellSizeArray();

    amrex::Real const inv_dy = 1./dx[1];
    if (Ms_hi_y == 0.){
        return inv_dy*(0. - DownwardDy(F, i, j, k, geom));
    } else if (Ms_lo_y == 0.){
        return inv_dy*(UpwardDy(F, i, j, k, geom) - 0.);
    } else {
        return inv_dy*(UpwardDy(F, i, j, k, geom) - DownwardDy(F, i, j, k, geom));
    }
 }


/**
  * Perform divergence of gradient along z on M field */
 AMREX_GPU_HOST_DEVICE AMREX_FORCE_INLINE
 static amrex::Real LaplacianDz_Mag (
    amrex::Array4<amrex::Real> const& F,
    amrex::Real const Ms_lo_z, amrex::Real const Ms_hi_z,
    int const i, int const j, int const k, const Geometry& geom) {

    // extract dx from the geometry object
    GpuArray<Real,AMREX_SPACEDIM> dx = geom.CellSizeArray();

    amrex::Real const inv_dz = 1./dx[2];
    if (Ms_hi_z == 0.){
        return inv_dz*(0. - DownwardDz(F, i, j, k, geom));
    } else if (Ms_lo_z == 0.){
        return inv_dz*(UpwardDz(F, i, j, k, geom) - 0.);
    } else {
        return inv_dz*(UpwardDz(F, i, j, k, geom) - DownwardDz(F, i, j, k, geom));
    }
 }

/**
  * Compute the sum to get Laplacian of M field */
AMREX_GPU_HOST_DEVICE AMREX_FORCE_INLINE
 static amrex::Real Laplacian_Mag (
     amrex::Array4<amrex::Real> const& F,
     amrex::Real const Ms_lo_x, amrex::Real const Ms_hi_x, amrex::Real const Ms_lo_y, amrex::Real const Ms_hi_y, amrex::Real const Ms_lo_z, amrex::Real const Ms_hi_z,
     int const i, int const j, int const k, const Geometry& geom) {

     //amrex::Print() << "This is called " << Ms_lo_x << "\n";
     return LaplacianDx_Mag(F, Ms_lo_x, Ms_hi_x, i, j, k, geom) + LaplacianDy_Mag(F, Ms_lo_y, Ms_hi_y, i, j, k, geom) + LaplacianDz_Mag(F, Ms_lo_z, Ms_hi_z, i, j, k, geom);
 }

